PROG=	nvram
MAN=	nvram.8

CFLAGS+=-DTARGET_OS_BRIDGE=0
LDADD+=-framework CoreFoundation -framework IOKit

BINDIR=/usr/sbin

.include <bsd.prog.mk>
