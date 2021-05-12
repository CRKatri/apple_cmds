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

.PATH: ${.CURDIR}/../cksum

CFLAGS+=-DENABLE_MD5 -DENABLE_RMD160 -DENABLE_SHA1 -DENABLE_SHA256
LDADD=-framework CoreFoundation

BINDIR=/usr/sbin

.include <bsd.prog.mk>
