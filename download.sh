#!/bin/sh
TEMP=$(mktemp -d)
wget -q -P${TEMP} https://opensource.apple.com/tarballs/${1}/${1}-${2}.tar.gz
tar xf ${TEMP}/${1}-${2}.tar.gz -C ${1} --strip-components=1
echo "${2}" > ${1}/.apple_version
