PROG=	mtree
MAN=	mtree.8
SRCS=	commoncrypto.c \
	compare.c \
	create.c \
	excludes.c \
	metrics.c \
	misc.c \
	mtree.c \
	spec.c \
	specspec.c \
	verify.c \
	crc.c

.PATH: ../cksum

LDADD=-framework CoreFoundation

.include <bsd.prog.mk>
