#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD$

PROG=	calendar
SRCS=	calendar.c day.c io.c ostern.c paskha.c

FILES=	calendars/calendar.freebsd
FILESDIR=	${SHAREDIR}/calendar

LDADD+=-liosexec

.include <bsd.prog.mk>
