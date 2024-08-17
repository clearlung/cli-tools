kernel=sys-kernel/vanilla-sources

echo "sys-kernel/linux-firmware linux-fw-redistributable" >> /etc/portage/package.license
emerge sys-kernel/linux-firmware

echo "sys-kernel/installkernel dracut grub" >> /etc/portage/package.use/installkernel
emerge sys-kernel/installkernel
#grub-install --efi-directory=/efi #assuming installkernel does this automatially 

echo "$kernel ~amd64" >> /etc/portage/package.accept_keywords/kernel
emerge $kernel

eselect kernel list
read -rp "Kernel: " kernelnum
eselect kernel set $kernelnum

cp /gentoo-installer/kernel/.config /usr/src/linux/
cd /usr/src/linux
make -j6 -l6 && make modules_install && make install
