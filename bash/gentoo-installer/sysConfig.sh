#editor=vim
#installerDir=/gentoo-installer

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
#$editor /etc/conf.d/keymaps
sed -i "s/us/mod-dh-ansi-us-wide" /etc/conf.d/keymaps
cp $installerDir/postinstall/mod-dh-ansi-us-wide.map.gz /usr/share/keymaps/i386/colemak
mkdir -p /etc/X11/xorg.conf.d
cp $installerDir/postinstall/xorg/00-keyboard.conf /etc/X11/xorg.conf.d/
ln -s -p /usr/share/X11/xkb/ /etc/X11/xkb/
cp $installerDir/postinstall/xorg/pc /etc/X11/xkb/symbols


emerge net-misc/dhcpcd
emerge net-wireless/wpa_supplicant
emerge net-misc/chrony
emerge app-admin/sysklogd
emerge app-shells/bash-completion

#essentials

rc-update add dhcpcd default
rc-update add wpa_supplicant default
rc-update add chronyd default
rc-update add sysklogd default
