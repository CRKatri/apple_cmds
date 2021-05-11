PROG=	rtadvd
MAN=	rtadvd.8 rtadvd.conf.5
SRCS=	advcap.c config.c dump.c if.c \
	rrenum.c rtadvd_logging.c rtadvd.c \
	timer.c

LDADD+=-lutil

BINDIR=/usr/sbin

.include <bsd.prog.mk>
