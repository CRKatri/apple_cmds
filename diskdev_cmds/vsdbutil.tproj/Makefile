PROG=	vsdbutil
MAN=	vsdbutil.8
SRCS=	vsdbutil_main.c \
	mount_flags.c

.PATH: ${.CURDIR}/../mount_flags_dir

LDADD+=-liosexec

BINDIR=/usr/sbin

.include <bsd.prog.mk>
