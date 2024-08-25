#installerDir=/gentoo-installer
#kernel=sys-kernel/vanilla-sources

echo "sys-kernel/linux-firmware linux-fw-redistributable" >> /etc/portage/package.license
emerge sys-kernel/linux-firmware

echo 'GRUB_PLATFORMS="efi-64"' >> /etc/portage/make.conf
emerge sys-boot/grub
grub-install --efi-directory=/efi

echo "sys-kernel/installkernel dracut grub" >> /etc/portage/package.use/installkernel
emerge sys-kernel/installkernel

echo "$kernel ~amd64" >> /etc/portage/package.accept_keywords/kernel
emerge $kernel

eselect kernel set 1

cp $installerDir/gentoo/kernel/.config /usr/src/linux/
cd /usr/src/linux
make -j6 -l6 && make modules_install && make install
