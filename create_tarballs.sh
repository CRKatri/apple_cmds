#!/bin/sh
if command -v bsdtar &>/dev/null; then
	TAR="bsdtar"
elif ! tar --version | grep "GNU" &>/dev/null; then
	TAR="tar"
else
	echo "Install BSD tar"
	exit 1
fi

num=0
for i in adv_cmds basic_cmds bootstrap_cmds \
		developer_cmds diskdev_cmds doc_cmds \
		file_cmds mail_cmds misc_cmds network_cmds \
		patch_cmds remote_cmds shell_cmds \
		system_cmds text_cmds; do
	EXTRA_PATHS=""
	TARFLAGS="caf"
	case "$i" in
		network_cmds) TARFLAGS="-s '|^|network_cmds/|' -caf" EXTRA_PATHS="lib/libpcap";;
		remote_cmds) TARFLAGS="-s '|^|remote_cmds/|' -caf" EXTRA_PATHS="lib/libtelnet";;
	esac
	num=$((num+1))
	printf "(%i) %s\n" "$num" "$i"
	${TAR} ${TARFLAGS} $i.tar.zst $i ${EXTRA_PATHS}
done