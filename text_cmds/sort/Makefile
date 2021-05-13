# $FreeBSD$

PROG=	sort

SRCS=	bwstring.c coll.c commoncrypto.c file.c \
	mem.c radixsort.c sort.c vsort.c

sort.1: sort.1.in
	sed ${MAN_SUB} ${.ALLSRC} >${.TARGET}

CLEANFILES+= sort.1

# Enabled here cause not enabling it is a bad default
CFLAGS+= -DSORT_THREADS
MAN_SUB+= -e 's|%%THREADS%%||g'

CFLAGS+= -DWITHOUT_NLS
MAN_SUB+= -e 's|%%NLS%%|\.\\"|g'

# Current text_cmds version
CFLAGS+=-DSORT_VERSION=\"106\"

.include <bsd.prog.mk>
