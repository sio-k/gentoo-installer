#!/usr/bin/env bash
set +e
set +u

MNAME=$(cat /machinename)

/gentoo-installer prepare $MNAME
cp -f /gentoo-installer /mnt/gentoo/gentoo-installer
chroot /mnt/gentoo /bin/bash -e \
	"source /etc/profile && /gentoo-installer primary ${MNAME} && exit"

# reboot into new system
reboot