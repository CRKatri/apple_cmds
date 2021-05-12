PROG=	chkpasswd
MAN=	chkpasswd.8
SRCS=	file_passwd.c pam_passwd.c \
	passwd.c stringops.c

LDADD+=-lpam

BINDIR=/usr/libexec

.include <bsd.prog.mk>
