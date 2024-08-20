#!/bin/bash
editor=vim
installerDir=/gentoo-installer

#fstab
lsblk

read -rp "root partition: " rootPartition 
read -rp "boot partition: " bootPartition #preferably convert partition identifier to UUID

echo "/dev/$rootPartition  / ext4  defaults  0 1" >> /etc/fstab
echo "/dev/$bootPartition  /efi  vfat  defaults  1 2" >> /etc/fstab

read -rp "hostname: " hostname
echo $hostname > /etc/hostname

#misc
passwd

#keyboard conf
$editor /etc/conf.d/keymaps
cp $installerDir/postinstall/mod-dh-ansi-us-wide.map.gz /usr/share/keymaps/i386/colemak
mkdir -p /etc/X11/xorg.conf.d
cp $installerDir/postinstall/xorg/00-keyboard.conf /etc/X11/xorg.conf.d/
mkdir -p /etc/X11/xkb/symbols
cp $installerDir/postinstall/xorg/pc /etc/X11/xkb/symbols

#essentials
emerge net-misc/dhcpcd
rc-update add dhcpcd default

emerge net-wireless/wpa_supplicant
rc-update add wpa_supplicant default

emerge net-misc/chrony
rc-update add chronyd default

emerge app-admin/sysklogd
rc-update add sysklogd default

emerge app-shells/bash-completion
