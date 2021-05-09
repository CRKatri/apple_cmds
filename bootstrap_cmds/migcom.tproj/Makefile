PROG=	migcom
SRCS=	error.c \
	global.c \
	header.c \
	mig.c \
	routine.c \
	server.c \
	statement.c \
	string.c \
	type.c \
	user.c \
	utils.c \
	lexxer.l \
	parser.y
SCRIPTS=	mig.sh

CFLAGS+=-DMIG_VERSION=\"mig-116.100.1\"

BINDIR=/usr/libexec/
SCRIPTSDIR=/usr/bin/

.include <bsd.prog.mk>
