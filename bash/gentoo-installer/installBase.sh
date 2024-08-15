editor=nano
region=America
cp /gentoo-installer/portage/make.conf /mnt/gentoo/etc/portage
cp --dereference /etc/resolv.conf /mnt/gentoo/etc
arch-chroot /mnt/gentoo

emerge-webrsync
emerge --oneshot app-portage/mirrorselect
mirrorselect -io >> /etc/portage/make.conf
emerge --oneshot app-portage/cpuid2cpuflags
echo "*/* $(cpuid2cpuflags)" > /etc/portage/package.use/00cpu-flags

ls -l /usr/share/zoneinfo/$region
read -sp "City: " city
echo "$region/$city" /etc/timezone
emerge --config sys-libs/timezone-data

$editor /etc/locale.gen
locale-gen
eselect locale list
read -sp "Locale: " locale
eselect locale set $locale
env-update && . /etc/profile

echo "sys-kernel/linux-firmeware linux-fw-redistributable" >> /etc/portage/package.license
emerge sys-kernel/linux-firmware
