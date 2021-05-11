PROG=	ecnprobe
MAN=	ecnprobe.1
SRCS=	capture.c ecn_probe.c ecn.c gmt2local.c \
	history.c inet.c session.c support.c

# libpcap sources
SRCS+= pcap.c bpf_filter.c gencode.c grammar.y \
	scanner.l nametoaddr.c optimize.c pcap-bpf.c \
	fad-getad.c pcap-darwin.c pcap-common.c \
	fmtutils.c pcap-util.c pcapng.c sf-pcapng.c \
	savefile.c sf-pcap.c

CLEANFILES=scanner.h
YFLAGS+=-p pcap_
LFLAGS+=-Ppcap_ --header-file=${.OBJDIR}/scanner.h --nounput

CFLAGS+=-I${.CURDIR}/../../lib/libpcap/libpcap/
CFLAGS+=-I${.OBJDIR} -I${.CURDIR} -DHAVE_CONFIG_H

gencode.o: scanner.c

.PATH: ${.CURDIR}/../../lib/libpcap/libpcap

BINDIR=/usr/bin

.include <bsd.prog.mk>
