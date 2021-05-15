#!/bin/sh
if command -v bsdtar >/dev/null 2>&1; then
	TAR="bsdtar"
elif ! tar --version | grep "GNU" >/dev/null 2>&1; then
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
	REGEX=""
	case "$i" in
		network_cmds) REGEX="|^|network_cmds/|" EXTRA_PATHS="lib/libpcap";;
		remote_cmds) REGEX="|^|remote_cmds/|" EXTRA_PATHS="lib/libtelnet";;
	esac
	num=$((num+1))
	printf "(%i) %s\n" "$num" "$i"
	cp setup.sh $i/setup.sh
	if [ "${REGEX}" == "" ]; then
		${TAR} -caf $i.tar.zst $i ${EXTRA_PATHS}
	else
		${TAR} -s ${REGEX} -caf $i.tar.zst $i ${EXTRA_PATHS}
	fi
	rm $i/setup.sh
done
