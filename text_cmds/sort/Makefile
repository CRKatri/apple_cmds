# $FreeBSD$

PROG=	sort

SRCS=	bwstring.c coll.c commoncrypto.c file.c \
	mem.c radixsort.c sort.c vsort.c

sort.1: sort.1.in
	sed ${MAN_SUB} ${.ALLSRC} >${.TARGET}

CLEANFILES+= sort.1

CFLAGS+= -DSORT_THREADS
MAN_SUB+= -e 's|%%THREADS%%||g'

# Current text_cmds version
CFLAGS+=-DSORT_VERSION=\"106\"

.include <bsd.prog.mk>
