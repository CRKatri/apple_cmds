#!/bin/sh
for pkg in adv_cmds basic_cmds bootstrap_cmds developer_cmds \
	diskdev_cmds doc_cmds file_cmds mail_cmds misc_cmds network_cmds \
	patch_cmds remote_cmds shell_cmds system_cmds text_cmds; do
	./download.sh "${pkg}"
done
