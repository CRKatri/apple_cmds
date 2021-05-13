RPCGEN?=rpcgen
STRIP=

SHAREDIR=/usr/share/

.if !defined(BINDIR)
BINDIR=/usr/bin
.endif

COMPRESS_CMD?=	zstd -c
COMPRESS_EXT?=	.zst
