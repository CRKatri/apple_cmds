PROG=	telnet
SRCS=	authenc.c commands.c main.c network.c \
	ring.c sys_bsd.c telnet.c terminal.c tn3270.c \
	utilities.c genget.c auth.c misc.c

CFLAGS+=-DTERMCAP -DKLUDGELINEMODE -DUSE_TERMIO -DENV_HACK \
	-DAUTHENTICATION -DSKEY -DIPSEC -DINET6 -DFORWARD  \
	-I${.CURDIR}/../../lib
   # -DENCRYPTION -DKRB4
LDADD=-lncursesw -lipsec

.PATH: ../../lib/libtelnet

.include <bsd.prog.mk>
