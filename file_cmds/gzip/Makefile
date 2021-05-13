PROG=	gzip
SRCS=	futimens.c \
	gzip.c
MAN=	gzexe.1 gzip.1 zdiff.1 zforce.1 zmore.1 znew.1
SCRIPTS=	gzexe \
	gzip \
	zdiff \
	zforce \
	zmore \
	znew

CFLAGS+=-DGZIP_APPLE_VERSION=\"321.40.3\"
LDADD=-llzma -lz -lbz2

BINDIR=/usr/bin

.include <bsd.prog.mk>
