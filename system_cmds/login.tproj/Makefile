PROG=	login
SRCS=	klogin.c login_audit.c login.c

# Setuid this bin
BINMODE=4555

CFLAGS+=-DUSE_BSD_AUDIT -DUSE_PAM

LDADD+=-lpam -liosexec

.include <bsd.prog.mk>
