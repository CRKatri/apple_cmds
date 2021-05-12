#	$NetBSD: Makefile,v 1.4 2011/02/16 01:31:33 joerg Exp $
#	$FreeBSD$
#	$OpenBSD: Makefile,v 1.6 2003/06/25 15:00:04 millert Exp $

PROG=	grep

SRCS=	file.c grep.c queue.c util.c

LINKS+=		${BINDIR}/grep ${BINDIR}/egrep \
		${BINDIR}/grep ${BINDIR}/fgrep \
		${BINDIR}/grep ${BINDIR}/rgrep \

MLINKS+=	grep.1 egrep.1 \
		grep.1 fgrep.1 \
		grep.1 rgrep.1

CFLAGS+=-DWITHOUT_FASTMATCH

LDADD+=-llzma -lbz2 -lz

.include <bsd.prog.mk>
