kernel="sys-kernel/vanilla-sources"


echo "sys-kernel/vanilla-sources ~amd64" >> /etc/portage/package.accept_keywords/kernel
emerge $kernel
eselect kernel list
read -sp "Kernel: " kernelnum
eselect kernel set $kernelnum

cp /gentoo-installer/kernel/.config /usr/src/linux/
cd /usr/src/linux
make -j6 -l6 && make modules_install && make install

echo "sys-kernel/installkernel dracut grub" >> /etc/portage/package.use/installkernel
#echo 'GRUB_PLATFORMS="efi-64"' >> /etc/portage/make.conf #only if it doesn't already exist
#echo "GRUB_CFG=/efi/EFI/Gentoo/grub.cfg" >> /etc/env.d/99grub && env-update #sets installkernel's default config file
emerge sys-kernel/installkernel
