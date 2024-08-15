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
$editor /etc/conf.d/keymaps
cp $installerDir/misc/mod-dh-ansi-us-wide.map.gz /usr/share/keymaps/i386/colemak

#bootloader
echo 'GRUB_PLATFORMS="efi-64"' >> /etc/portage/make.conf
emerge grub
grub-install --efi-directory=/efi
grub-mkconfig -o /boot/grub/grub.cfg

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
