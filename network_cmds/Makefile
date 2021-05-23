SUBDIR=	arp.tproj \
	cfilutil \
	dnctl \
	ecnprobe \
	frame_delay \
	ifconfig.tproj \
	ip6addrctl.tproj \
	kdumpd.tproj \
	mnc.tproj \
	mptcp_client \
	mtest.tproj \
	ndp.tproj \
	ping.tproj \
	ping6.tproj \
	pktapctl \
	pktmnglr \
	rarpd.tproj \
	route.tproj \
	rtadvd.tproj \
	rtsol.tproj \
	spray.tproj \
	traceroute.tproj \
	traceroute6.tproj

.if !defined(MK_NETSTAT)
MK_NETSTAT=no
.endif

# netstat doesnt build on iOS 12, if building for higher set MK_NETSTAT to yes
.if ${MK_NETSTAT} == "yes"
SUBDIR+=	netstat.tproj
.endif

.include <bsd.subdir.mk>
