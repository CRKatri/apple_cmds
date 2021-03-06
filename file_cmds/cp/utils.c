/*-
 * Copyright (c) 1991, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef lint
#if 0
static char sccsid[] = "@(#)utils.c	8.3 (Berkeley) 4/1/94";
#endif
#endif /* not lint */
#include <sys/cdefs.h>
__FBSDID("$FreeBSD: src/bin/cp/utils.c,v 1.46 2005/09/05 04:36:08 csjp Exp $");

#include <sys/types.h>
#include <sys/acl.h>
#include <sys/param.h>
#include <sys/stat.h>
#ifdef VM_AND_BUFFER_CACHE_SYNCHRONIZED
#include <sys/mman.h>
#endif

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <fts.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>
#include <locale.h>

#ifdef __APPLE__
#include <sys/time.h>
#include <copyfile.h>
#include <string.h>
#include <sys/mount.h>
#include <get_compat.h> 
#include <sys/attr.h>
#include <sys/clonefile.h>
#else 
#define COMPAT_MODE(a,b) (1)
#endif /* __APPLE__ */

#if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ < 140000
int rpmatch(const char *);
#endif

#include "extern.h"
#define	cp_pct(x,y)	(int)(100.0 * (double)(x) / (double)(y))

/* Memory strategy threshold, in pages: if physmem is larger then this, use a 
 * large buffer */
#define PHYSPAGES_THRESHOLD (32*1024)

/* Maximum buffer size in bytes - do not allow it to grow larger than this */
#define BUFSIZE_MAX (2*1024*1024)

/* Small (default) buffer size in bytes. It's inefficient for this to be
 * smaller than MAXPHYS */
#define BUFSIZE_SMALL (MAXPHYS)

int
copy_file(const FTSENT *entp, int dne)
{
	static char *buf = NULL;
	static size_t bufsize;
	struct stat *fs;
	int ch, checkch, from_fd, rval, to_fd;
	ssize_t rcount;
	ssize_t wcount;
	size_t wresid;
	off_t wtotal;
	char *bufp;
	char resp[] = {'\0', '\0'};
#ifdef VM_AND_BUFFER_CACHE_SYNCHRONIZED
	char *p;
#endif
	mode_t mode = 0;
	struct stat to_stat;

	if ((from_fd = open(entp->fts_path, O_RDONLY, 0)) == -1) {
		warn("%s", entp->fts_path);
		return (1);
	}

	fs = entp->fts_statp;

	/*
	 * If the file exists and we're interactive, verify with the user.
	 * If the file DNE, set the mode to be the from file, minus setuid
	 * bits, modified by the umask; arguably wrong, but it makes copying
	 * executables work right and it's been that way forever.  (The
	 * other choice is 666 or'ed with the execute bits on the from file
	 * modified by the umask.)
	 */
	if (!dne) {
#define YESNO "(y/n [n]) "
		if (nflag) {
			if (vflag)
				printf("%s not overwritten\n", to.p_path);
			(void)close(from_fd);
			return (1);
		} else if (iflag) {
			(void)fprintf(stderr, "overwrite %s? %s", 
					to.p_path, YESNO);

			/* Load user specified locale */
			setlocale(LC_MESSAGES, "");

			checkch = ch = getchar();
			while (ch != '\n' && ch != EOF)
				ch = getchar();

			/* only care about the first character */
			resp[0] = checkch;

			if (rpmatch(resp) != 1) {
				(void)close(from_fd);
				(void)fprintf(stderr, "not overwritten\n");
				return (1);
			}
		}
		
		if (cflag) {
			(void)unlink(to.p_path);
			int error = clonefile(entp->fts_path, to.p_path, 0);
			if (error)
				warn("%s: clonefile failed", to.p_path);
			(void)close(from_fd);
			return error == 0 ? 0 : 1;
		}

		if (COMPAT_MODE("bin/cp", "unix2003")) {
		    /* first try to overwrite existing destination file name */
		    to_fd = open(to.p_path, O_WRONLY | O_TRUNC, 0);
		    if (to_fd == -1) {
			if (fflag) {
			    /* Only if it fails remove file and create a new one */
			    (void)unlink(to.p_path);
			    to_fd = open(to.p_path, O_WRONLY | O_TRUNC | O_CREAT,
					 fs->st_mode & ~(S_ISUID | S_ISGID));
			}
		    }
		} else {
			if (fflag) {
			    /* remove existing destination file name, 
			     * create a new file  */
			    (void)unlink(to.p_path);
			    to_fd = open(to.p_path, O_WRONLY | O_TRUNC | O_CREAT,
					 fs->st_mode & ~(S_ISUID | S_ISGID));
			} else 
			    /* overwrite existing destination file name */
			    to_fd = open(to.p_path, O_WRONLY | O_TRUNC, 0);
		}
	} else {

		if (cflag) {
			int error = clonefile(entp->fts_path, to.p_path, 0);
			if (error)
				warn("%s: clonefile failed", to.p_path);
			(void)close(from_fd);
			return error == 0 ? 0 : 1;
		}

		to_fd = open(to.p_path, O_WRONLY | O_TRUNC | O_CREAT,
		    fs->st_mode & ~(S_ISUID | S_ISGID));
	}

	if (to_fd == -1) {
		warn("%s", to.p_path);
		(void)close(from_fd);
		return (1);
	}

	rval = 0;

#ifdef __APPLE__
       if (S_ISREG(fs->st_mode)) {
               struct statfs sfs;

               /*
                * Pre-allocate blocks for the destination file if it
                * resides on Xsan.
                */
               if (fstatfs(to_fd, &sfs) == 0 &&
                   strcmp(sfs.f_fstypename, "acfs") == 0) {
                       fstore_t fst;

                       fst.fst_flags = 0;
                       fst.fst_posmode = F_PEOFPOSMODE;
                       fst.fst_offset = 0;
                       fst.fst_length = fs->st_size;

                       (void) fcntl(to_fd, F_PREALLOCATE, &fst);
               }
       }
#endif /* __APPLE__ */

       if (fstat(to_fd, &to_stat) != -1) {
	       mode = to_stat.st_mode;
	       if ((mode & (S_IRWXG|S_IRWXO))
		   && fchmod(to_fd, mode & ~(S_IRWXG|S_IRWXO))) {
		       if (errno != EPERM) /* we have write access but do not own the file */
			       warn("%s: fchmod failed", to.p_path);
		       mode = 0;
	       }
       } else {
	       warn("%s", to.p_path);
       }
	/*
	 * Mmap and write if less than 8M (the limit is so we don't totally
	 * trash memory on big files.  This is really a minor hack, but it
	 * wins some CPU back.
	 */
#ifdef VM_AND_BUFFER_CACHE_SYNCHRONIZED
	if (S_ISREG(fs->st_mode) && fs->st_size > 0 &&
	    fs->st_size <= 8 * 1048576) {
		if ((p = mmap(NULL, (size_t)fs->st_size, PROT_READ,
		    MAP_SHARED, from_fd, (off_t)0)) == MAP_FAILED) {
			warn("%s", entp->fts_path);
			rval = 1;
		} else {
			wtotal = 0;
			for (bufp = p, wresid = fs->st_size; ;
			    bufp += wcount, wresid -= (size_t)wcount) {
				wcount = write(to_fd, bufp, wresid);
				wtotal += wcount;
				if (info) {
					info = 0;
					(void)fprintf(stderr,
						"%s -> %s %3d%%\n",
						entp->fts_path, to.p_path,
						cp_pct(wtotal, fs->st_size));
						
				}
				if (wcount >= (ssize_t)wresid || wcount <= 0)
					break;
			}
			if (wcount != (ssize_t)wresid) {
				warn("%s", to.p_path);
				rval = 1;
			}
			/* Some systems don't unmap on close(2). */
			if (munmap(p, fs->st_size) < 0) {
				warn("%s", entp->fts_path);
				rval = 1;
			}
		}
	} else
#endif
	{
		if (buf == NULL) {
			/*
			 * Note that buf and bufsize are static. If
			 * malloc() fails, it will fail at the start
			 * and not copy only some files. 
			 */ 
			if (sysconf(_SC_PHYS_PAGES) > 
			    PHYSPAGES_THRESHOLD)
				bufsize = MIN(BUFSIZE_MAX, MAXPHYS * 8);
			else
				bufsize = BUFSIZE_SMALL;
			buf = malloc(bufsize);
			if (buf == NULL)
				err(1, "Not enough memory");
		}
		wtotal = 0;
		while ((rcount = read(from_fd, buf, bufsize)) > 0) {
			for (bufp = buf, wresid = rcount; ;
			    bufp += wcount, wresid -= wcount) {
				wcount = write(to_fd, bufp, wresid);
				wtotal += wcount;
				if (info) {
					info = 0;
					(void)fprintf(stderr,
						"%s -> %s %3d%%\n",
						entp->fts_path, to.p_path,
						cp_pct(wtotal, fs->st_size));
						
				}
				if (wcount >= (ssize_t)wresid || wcount <= 0)
					break;
			}
			if (wcount != (ssize_t)wresid) {
				warn("%s", to.p_path);
				rval = 1;
				break;
			}
		}
		if (rcount < 0) {
			warn("%s", entp->fts_path);
			rval = 1;
		}
	}

	/*
	 * Don't remove the target even after an error.  The target might
	 * not be a regular file, or its attributes might be important,
	 * or its contents might be irreplaceable.  It would only be safe
	 * to remove it if we created it and its length is 0.
	 */
	if (mode != 0)
		if (fchmod(to_fd, mode))
			warn("%s: fchmod failed", to.p_path);
#ifdef __APPLE__
	/* do these before setfile in case copyfile changes mtime */
	if (!Xflag && S_ISREG(fs->st_mode)) { /* skip devices, etc */
		if (fcopyfile(from_fd, to_fd, NULL, COPYFILE_XATTR) < 0)
			warn("%s: could not copy extended attributes to %s", entp->fts_path, to.p_path);
	}
	if (pflag && setfile(fs, to_fd))
		rval = 1;
	if (pflag) {
		/* If this ACL denies writeattr then setfile will fail... */
		if (fcopyfile(from_fd, to_fd, NULL, COPYFILE_ACL) < 0)
			warn("%s: could not copy ACL to %s", entp->fts_path, to.p_path);
	}
#else  /* !__APPLE__ */
	if (pflag && setfile(fs, to_fd))
		rval = 1;
	if (pflag && preserve_fd_acls(from_fd, to_fd) != 0)
		rval = 1;
#endif /* __APPLE__ */
	(void)close(from_fd);
	if (close(to_fd)) {
		warn("%s", to.p_path);
		rval = 1;
	}
	return (rval);
}

int
copy_link(const FTSENT *p, int exists)
{
	ssize_t len;
	char llink[PATH_MAX];

	if ((len = readlink(p->fts_path, llink, sizeof(llink) - 1)) == -1) {
		warn("readlink: %s", p->fts_path);
		return (1);
	}
	llink[len] = '\0';
	if (exists && unlink(to.p_path)) {
		warn("unlink: %s", to.p_path);
		return (1);
	}
	if (symlink(llink, to.p_path)) {
		warn("symlink: %s", llink);
		return (1);
	}
#ifdef __APPLE__
	if (!Xflag)
		if (copyfile(p->fts_path, to.p_path, NULL, COPYFILE_XATTR | COPYFILE_NOFOLLOW_SRC) <0)
			warn("%s: could not copy extended attributes to %s",
			     p->fts_path, to.p_path);
#endif
	return (pflag ? setfile(p->fts_statp, -1) : 0);
}

int
copy_fifo(struct stat *from_stat, int exists)
{
	if (exists && unlink(to.p_path)) {
		warn("unlink: %s", to.p_path);
		return (1);
	}
	if (mkfifo(to.p_path, from_stat->st_mode)) {
		warn("mkfifo: %s", to.p_path);
		return (1);
	}
	return (pflag ? setfile(from_stat, -1) : 0);
}

int
copy_special(struct stat *from_stat, int exists)
{
	if (exists && unlink(to.p_path)) {
		warn("unlink: %s", to.p_path);
		return (1);
	}
	if (mknod(to.p_path, from_stat->st_mode, from_stat->st_rdev)) {
		warn("mknod: %s", to.p_path);
		return (1);
	}
	return (pflag ? setfile(from_stat, -1) : 0);
}

int
setfile(struct stat *fs, int fd)
{
	struct attrlist ts_req = {};
	struct stat ts;
	int rval, gotstat, islink, fdval;
	struct {
		struct timespec mtime;
		struct timespec atime;
	} set_ts;

	rval = 0;
	fdval = fd != -1;
	islink = !fdval && S_ISLNK(fs->st_mode);
	fs->st_mode &= S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO;
	unsigned int options = islink ? FSOPT_NOFOLLOW : 0;

	ts_req.bitmapcount = ATTR_BIT_MAP_COUNT;
	ts_req.commonattr = ATTR_CMN_MODTIME | ATTR_CMN_ACCTIME;
	set_ts.mtime = fs->st_mtimespec;
	set_ts.atime = fs->st_atimespec;

	if (fdval ? fsetattrlist(fd, &ts_req, &set_ts, sizeof(set_ts), options) :
		    setattrlist(to.p_path, &ts_req, &set_ts, sizeof(set_ts), options)) {
		warn("%ssetattrlist: %s", fdval ? "f" : "", to.p_path);
		rval = 1;
	}
	if (fdval ? fstat(fd, &ts) : (islink ? lstat(to.p_path, &ts) :
				      stat(to.p_path, &ts))) {
		gotstat = 0;
	} else {
		gotstat = 1;
		ts.st_mode &= S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO;
	}
	/*
	 * Changing the ownership probably won't succeed, unless we're root
	 * or POSIX_CHOWN_RESTRICTED is not set.  Set uid/gid before setting
	 * the mode; current BSD behavior is to remove all setuid bits on
	 * chown.  If chown fails, lose setuid/setgid bits.
	 */
	if (!gotstat || fs->st_uid != ts.st_uid || fs->st_gid != ts.st_gid) {
		if (fdval ? fchown(fd, fs->st_uid, fs->st_gid) : (islink ?
								  lchown(to.p_path, fs->st_uid, fs->st_gid) :
								  chown(to.p_path, fs->st_uid, fs->st_gid))) {
			    if (errno != EPERM) {
				    warn("%schown: %s", fdval ? "f" : (islink ? "l" : ""), to.p_path);
				    rval = 1;
			    }
			    fs->st_mode &= ~(S_ISUID | S_ISGID);
		    }
	}

	if (!gotstat || fs->st_mode != ts.st_mode) {
		if (fdval ? fchmod(fd, fs->st_mode) : (islink ?
						       lchmod(to.p_path, fs->st_mode) :
						       chmod(to.p_path, fs->st_mode))) {
			warn("%schmod: %s", fdval ? "f" : (islink ? "l" : ""), to.p_path);
			rval = 1;
		}
	}

	if (!gotstat || fs->st_flags != ts.st_flags) {
		if (fdval ? fchflags(fd, fs->st_flags) : (islink ?
							  lchflags(to.p_path, fs->st_flags) :
							  chflags(to.p_path, fs->st_flags))) {
			if (errno != EPERM) {
				warn("%schflags: %s", fdval ? "f" : (islink ? "l" : ""), to.p_path);
				rval = 1;
			}
		}
	}
	return (rval);
}

#ifndef __APPLE__
int
preserve_fd_acls(int source_fd, int dest_fd)
{
	struct acl *aclp;
	acl_t acl;

	if (fpathconf(source_fd, _PC_ACL_EXTENDED) != 1 ||
	    fpathconf(dest_fd, _PC_ACL_EXTENDED) != 1)
		return (0);
	acl = acl_get_fd(source_fd);
	if (acl == NULL) {
		warn("failed to get acl entries while setting %s", to.p_path);
		return (1);
	}
	aclp = &acl->ats_acl;
	if (aclp->acl_cnt == 3)
		return (0);
	if (acl_set_fd(dest_fd, acl) < 0) {
		warn("failed to set acl entries for %s", to.p_path);
		return (1);
	}
	return (0);
}

int
preserve_dir_acls(struct stat *fs, char *source_dir, char *dest_dir)
{
	acl_t (*aclgetf)(const char *, acl_type_t);
	int (*aclsetf)(const char *, acl_type_t, acl_t);
	struct acl *aclp;
	acl_t acl;

	if (pathconf(source_dir, _PC_ACL_EXTENDED) != 1 ||
	    pathconf(dest_dir, _PC_ACL_EXTENDED) != 1)
		return (0);
	/*
	 * If the file is a link we will not follow it
	 */
	if (S_ISLNK(fs->st_mode)) {
		aclgetf = acl_get_link_np;
		aclsetf = acl_set_link_np;
	} else {
		aclgetf = acl_get_file;
		aclsetf = acl_set_file;
	}
	/*
	 * Even if there is no ACL_TYPE_DEFAULT entry here, a zero
	 * size ACL will be returned. So it is not safe to simply
	 * check the pointer to see if the default ACL is present.
	 */
	acl = aclgetf(source_dir, ACL_TYPE_DEFAULT);
	if (acl == NULL) {
		warn("failed to get default acl entries on %s",
		    source_dir);
		return (1);
	}
	aclp = &acl->ats_acl;
	if (aclp->acl_cnt != 0 && aclsetf(dest_dir,
	    ACL_TYPE_DEFAULT, acl) < 0) {
		warn("failed to set default acl entries on %s",
		    dest_dir);
		return (1);
	}
	acl = aclgetf(source_dir, ACL_TYPE_ACCESS);
	if (acl == NULL) {
		warn("failed to get acl entries on %s", source_dir);
		return (1);
	}
	aclp = &acl->ats_acl;
	if (aclsetf(dest_dir, ACL_TYPE_ACCESS, acl) < 0) {
		warn("failed to set acl entries on %s", dest_dir);
		return (1);
	}
	return (0);
}
#endif /* !__APPLE__ */

void
usage(void)
{

	if (COMPAT_MODE("bin/cp", "unix2003")) {
	(void)fprintf(stderr, "%s\n%s\n",
"usage: cp [-R [-H | -L | -P]] [-fi | -n] [-apvXc] source_file target_file",
"       cp [-R [-H | -L | -P]] [-fi | -n] [-apvXc] source_file ... "
"target_directory");
	} else {
	(void)fprintf(stderr, "%s\n%s\n",
"usage: cp [-R [-H | -L | -P]] [-f | -i | -n] [-apvXc] source_file target_file",
"       cp [-R [-H | -L | -P]] [-f | -i | -n] [-apvXc] source_file ... "
"target_directory");
	}
	exit(EX_USAGE);
}
