#!/bin/bash
editor=nano

read -sp "boot partition: " bootPartition
read -sp "root partition: " rootPartition 

echo "$rootPartition  / ext4  defaults  0 1" >> /etc/fstab
echo "$bootPartition  /efi  vfat  defaults  1 2" >> /etc/fstab

read -sp "hostname: " hostname
echo $hostname > /etc/hostname

passwd
$editor /etc/conf.d/keymaps

#essentials
echo "sys-kernel/linux-firmware linux-fw-redistributable" >> /etc/portage/package.license
emerge sys-kernel/linux-firmware

emerge net-misc/dhcpcd
rc-update add dhcpcd default

emerge net-wireless/wpa_supplicant
rc-update add wpa_supplicant default

emerge net-misc/chrony
rc-update add chronyd default

emerge app-admin/sysklogd
rc-update add sysklogd default

emerge app-shells/bash-completion
