PROG=	compress
MAN=	compress.1 uncompress.1 zopen.3
SRCS=	compress.c zopen.c
SCRIPTS=	zcat.sh

BINDIR=/usr/bin

LINKS+=	${BINDIR}/compress ${BINDIR}/uncompress

CFLAGS+=-I${.CURDIR}/../common

.include <bsd.prog.mk>
