PROG=	telnetd
MAN=	telnetd.8

SRCS=	global.c slc.c state.c sys_term.c telnetd.c \
	termstat.c utility.c getent.c

BINDIR=/usr/libexec

CFLAGS+= -DNO_UTMP -DLINEMODE -DKLUDGELINEMODE -DUSE_TERMIO \
	-DDIAGNOSTICS -DOLD_ENVIRON -DENV_HACK -DINET6 \
	-I${.CURDIR}/../../lib
LDADD=-lncursesw

.PATH: ../../lib/libtelnet

.include <bsd.prog.mk>
