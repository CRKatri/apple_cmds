PROG=	atrun
MAN=	atrun.8
SRCS=	atrun.c gloadavg.c

LDADD+=-liosexec

CFLAGS+=-I${.CURDIR}/../at.tproj -DPROC_DIR=\"/proc\"

BINDIR=/usr/libexec

.include <bsd.prog.mk>
