# $FreeBSD$

CFLAGS+= -DHAS_NCURSES -DHAS_UNISTD -DHAS_STDARG -DHAS_STDLIB \
	 -DHAS_SYS_WAIT

PROG=	ee
LINKS=	${BINDIR}/ee ${BINDIR}/ree ${BINDIR}/ee ${BINDIR}/edit
MLINKS=	ee.1 ree.1 ee.1 edit.1
LDADD+=-lncursesw -liosexec

.include <bsd.prog.mk>
