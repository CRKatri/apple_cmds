PROG=	gcore
MAN=	gcore-internal.1 gcore.1
SRCS=	convert.c corefile.c dyld_shared_cache.c \
	dyld.c main.c sparse.c threads.c utils.c \
	vanilla.c vm.c

LDADD+=-lutil -lcompression

.include <bsd.prog.mk>
