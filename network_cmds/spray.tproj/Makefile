PROG=	spray
MAN=	spray.8
SRCS=	spray.c spray_xdr.c spray.h
RPCSRC=	spray.x
CLEANFILES+=	spray_xdr.c spray.h

spray.h: ${RPCSRC}
	${RPCGEN} -h -o ${.TARGET} ${RPCSRC}

spray_xdr.c: ${RPCSRC}
	${RPCGEN} -c -o ${.TARGET} ${RPCSRC}

BINDIR=/usr/sbin

.include <bsd.prog.mk>
