#!/bin/sh
mkdir -p base/include/sys/ base/include/os/ base/lib/ base/include/System/uuid/ base/include/System/sys/ base/include/CommonCrypto base/include/bsm base/include/corecrypto base/include/firehose base/include/machine base/include/System/arm base/include/rpc base/include/mach-o base/include/libkern base/include/Kernel/kern base/include/dispatch base/include/IOkit/kext base/include/kern base/include/Kernel/IOKit base/include/Kernel/libkern base/include/mach_debug base/include/pthread

cp -af ${MACOSX_SYSROOT}/usr/include/tzfile.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/launch.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/sys/user.h base/include/sys/
cp -af ${MACOSX_SYSROOT}/usr/include/xpc base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/libproc.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/nlist.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/sys/resourcevar.h base/include/sys
cp -af ${MACOSX_SYSROOT}/usr/include/mach base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/get_compat.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/sys/ioctl_compat.h base/include/sys
cp -af ${MACOSX_SYSROOT}/usr/include/sys/ttychars.h base/include/sys
cp -af ${MACOSX_SYSROOT}/usr/include/sys/ttydev.h base/include/sys
cp -af ${MACOSX_SYSROOT}/usr/include/sys/tty.h base/include/sys
cp -af ${MACOSX_SYSROOT}/usr/include/sys/reboot.h base/include/sys/
cp -af ${MACOSX_SYSROOT}/usr/include/sys/disk.h base/include/sys/
cp -af ${MACOSX_SYSROOT}/usr/include/sys/vnode.h base/include/sys/
cp -af ${MACOSX_SYSROOT}/usr/include/sys/vnioctl.h base/include/sys/
cp -af ${MACOSX_SYSROOT}/usr/include/sys/conf.h base/include/sys/
cp -af ${MACOSX_SYSROOT}/usr/include/nameser.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/arpa base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/protocols base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/histedit.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/sys/acct.h base/include/sys/
cp -af ${MACOSX_SYSROOT}/usr/include/struct.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/vproc.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/bootstrap.h base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/servers base/include/
cp -af ${MACOSX_SYSROOT}/usr/include/timeconv.h base/include/
cp -rf ${MACOSX_SYSROOT}/System/Library/Frameworks/IOKit.framework/Headers/ base/include/IOKit
cp -af /usr/include/stdalign.h base/include/
sed -E s/'__IOS_PROHIBITED|__TVOS_PROHIBITED|__WATCHOS_PROHIBITED'//g < $TARGET_SYSROOT/usr/include/stdlib.h > base/include/stdlib.h

# iOS 12.0 XNU for maximum compatibility
# iOS 12.0 (4903.202.2) source is missing so we use a slightly newer one from between
# 12.1 beta 2 and beta 3
XNUVER="4903.221.2"
DISPATCHVER="1008.270.1"

wget -nc -Pbase/include https://opensource.apple.com/source/Libc/Libc-1439.40.11/nls/FreeBSD/msgcat.h
wget -nc -Pbase/include https://opensource.apple.com/source/libmalloc/libmalloc-317.40.8/private/stack_logging.h
wget -nc -Pbase/include/os https://opensource.apple.com/source/Libc/Libc-1439.40.11/os/assumes.h
wget -nc -Pbase/include https://opensource.apple.com/source/Libc/Libc-1439.40.11/include/libc.h
wget -nc -Pbase/include https://opensource.apple.com/source/libplatform/libplatform-126.1.2/include/_simple.h
wget -nc -Pbase/include/os https://opensource.apple.com/source/libplatform/libplatform-126.1.2/include/os/base_private.h
wget -nc -Pbase/include/System/uuid/ https://opensource.apple.com/source/Libc/Libc-1439.40.11/uuid/namespace.h
wget -nc -Pbase/include https://opensource.apple.com/source/libutil/libutil-58.40.2/mntopts.h
wget -nc -Pbase/include https://opensource.apple.com/source/libutil/libutil-58.40.2/libutil.h
wget -nc -Pbase/include https://opensource.apple.com/source/Libinfo/Libinfo-542.40.3/membership.subproj/membershipPriv.h
wget -nc -Pbase/include/rpc https://opensource.apple.com/source/Libinfo/Libinfo-542.40.3/rpc.subproj/pmap_clnt.h
wget -nc -Pbase/include/CommonCrypto https://opensource.apple.com/source/CommonCrypto/CommonCrypto-60118.30.2/include/CommonDigestSPI.h
wget -nc -Pbase/include \
	https://opensource.apple.com/source/launchd/launchd-842.92.1/liblaunch/vproc_priv.h \
	https://opensource.apple.com/source/launchd/launchd-842.92.1/liblaunch/reboot2.h \
	https://opensource.apple.com/source/launchd/launchd-842.92.1/liblaunch/bootstrap_priv.h
wget -nc -Pbase/include/bsm \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/bsm/audit_kevents.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/bsm/audit_record.h
chmod -Rf u+w base/include
wget -nc -Pbase/include/libkern \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/libkern/OSTypes.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/libkern/OSReturn.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/libkern/OSKextLib.h
wget -nc -Pbase/include/Kernel/libkern \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/libkern/OSKextLibPrivate.h
wget -nc -Pbase/include/System/libkern \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/libkern/OSKextLibPrivate.h
wget -nc -Pbase/include/os \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/os/log_private.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/os/log.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/os/atomic_private.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/os/atomic_private_arch.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/os/atomic_private_impl.h
wget -nc -Pbase/include/firehose \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/firehose/tracepoint_private.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libkern/firehose/firehose_types_private.h
wget -nc -Pbase/include/machine https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/machine/cpu_capabilities.h
wget -nc -Pbase/include/Kernel/kern https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/kern/ledger.h
wget -nc -Pbase/include/kern \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/kern/debug.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/kern/kern_types.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/kern/kcdata.h
wget -nc -Pbase/include/System/machine https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/machine/cpu_capabilities.h
wget -nc -Pbase/include/System/arm https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/arm/cpu_capabilities.h
wget -nc -Pbase/include/mach https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/mach/coalition.h
wget -nc -Pbase/include/mach https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/mach/vm_statistics.h
ln -sf mach/vm_statistics.h base/include/vm_statistics.h
wget -nc -Pbase/include/netinet6 \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet6/in6_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet6/in6_pcb.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet6/mld6_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet6/ip6_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet6/raw_ip6.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet6/in6.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet6/nd6.h
wget -nc -Pbase/include/netinet \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/in.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/ip_flowid.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/tcp.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/if_ether.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/ip_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/icmp_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/igmp_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/tcpip.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/tcp_seq.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/tcp_fsm.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/udp_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/in_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/in_stat.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/in_pcb.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/tcp_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/mptcp_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/netinet/ip_dummynet.h
wget -nc -Pbase/include/net \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/route.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/net_perf.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/packet_mangler.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/pktap.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/bpf.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/iptap.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_media.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_bond_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_6lowpan_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_bond_internal.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_bridgevar.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/lacp.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_mib.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/network_agent.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_fake_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_vlan_var.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_arp.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/net_api_stats.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/if_llreach.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/ntstat.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/radix.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/content_filter.h
wget -nc -Pbase/include/net/pktsched \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/pktsched/pktsched.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/pktsched/pktsched_tcq.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/pktsched/pktsched_qfq.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/pktsched/pktsched_fq_codel.h
wget -nc -Pbase/include/net/classq \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/classq/if_classq.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/classq/classq_red.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/classq/classq_blue.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/classq/classq_rio.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/classq/classq_sfb.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/net/classq/classq.h
wget -nc -Pbase/include/sys \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/socket.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/socketvar.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/event.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/mbuf.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/mbuf.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/kern_control.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/kern_event.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/sys_domain.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/ipcs.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/sem_internal.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/shm_internal.h \
	https://opensource.apple.com/source/xnu/xnu-1228.3.13/bsd/sys/mtio.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/unpcb.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/pgo.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/kdebug.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys_private/kdebug_private.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/proc_info.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/kern_memorystatus.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/ptrace.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/stackshot.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/spawn_internal.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/resource.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/sockio.h
wget -nc -Pbase/include/corecrypto \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/EXTERNAL_HEADERS/corecrypto/ccsha2.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/EXTERNAL_HEADERS/corecrypto/ccdigest.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/EXTERNAL_HEADERS/corecrypto/cc.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/EXTERNAL_HEADERS/corecrypto/cc_config.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/EXTERNAL_HEADERS/corecrypto/ccn.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/EXTERNAL_HEADERS/corecrypto/cc_error.h
wget -nc -Pbase/include/System/sys \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/proc.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/proc_uuid_policy.h \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/sys/kdebug.h
wget -nc -Pbase/include/dispatch \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/queue_private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/workloop_private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/source_private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/mach_private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/data_private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/io_private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/layout_private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/time_private.h \
	https://opensource.apple.com/source/libdispatch/libdispatch-${DISPATCHVER}/private/benchmark.h
wget -nc -Pbase/include/IOKit \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/iokit/IOKit/IOKitKeysPrivate.h
wget -nc -Pbase/include/Kernel/IOKit \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/iokit/IOKit/IOKitDebug.h
wget -nc -Pbase/include/IOKit/kext \
	https://opensource.apple.com/source/IOKitUser/IOKitUser-1845.81.1/kext.subproj/kextmanager_types.h \
	https://opensource.apple.com/source/IOKitUser/IOKitUser-1845.81.1/kext.subproj/OSKext.h
wget -nc -Pbase/include \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libsyscall/wrappers/spawn/spawn_private.h
rm base/include/mach/mach_init.h
wget -nc -Pbase/include/mach \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/libsyscall/mach/mach/mach_init.h
wget -nc -Pbase/include/mach_debug \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/osfmk/mach_debug/ipc_info.h
wget -nc -Pbase/include/mach-o \
	https://opensource.apple.com/source/dyld/dyld-832.7.3/include/mach-o/dyld_process_info.h
wget -nc -Pbase/include/pthread \
	https://opensource.apple.com/source/xnu/xnu-${XNUVER}/bsd/pthread/priority_private.h \
	https://opensource.apple.com/source/libpthread/libpthread-454.100.8/private/pthread/qos.h

sed -i'' -E 's/__API_UNAVAILABLE\(.*\)//g' base/include/mach-o/dyld_process_info.h
sed -i'' -E 's/API_AVAILABLE\(.*\)//g' base/include/dispatch/mach_private.h
sed -i'' -E 's/API_AVAILABLE\(.*\)//g' base/include/dispatch/data_private.h
sed -i'' -E 's/#if INET6/#ifdef INET6/g' base/include/sys/sockio.h
sed -i'' -E 's/^__OSX_AVAILABLE_STARTING\(.*\)//g' base/include/xpc/xpc.h
