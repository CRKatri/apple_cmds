#!/bin/sh
version="$(basename $(curl -s https://opensource.apple.com/tarballs/${1}/ | \
	pup 'table tbody tr td a:not([href="./../"]) text{}' -c | \
	sort -V | tail -n 1) .tar.gz | \
	rev | cut -d- -f 1 | rev)"
if [ "$( echo -e "${version}\n$(cat ${1}/.apple_version)" | sort -V | tail -n 1)" = "$(cat ${1}/.apple_version)" ]; then
	echo "${1} - $(cat ${1}/.apple_version)"
else
	echo "${1} - $(cat ${1}/.apple_version) -> ${version}"
	TEMP=$(mktemp -d)
	wget -q -P${TEMP} https://opensource.apple.com/tarballs/${1}/${1}-${version}.tar.gz
	tar xf ${TEMP}/${1}-${2}.tar.gz -C ${1} --strip-components=1
	echo "${version}" > ${1}/.apple_version
fi
