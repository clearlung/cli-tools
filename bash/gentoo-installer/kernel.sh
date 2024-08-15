kernel="sys-kernel/vanilla-sources"
echo "$kernel ~amd64" >> /etc/portage/package.accept_keywords/kernel
emerge $kernel

eselect kernel list
read -sp "Kernel: " kernelnum
eselect kernel set $kernelnum

cp /gentoo-installer/kernel/.config /usr/src/linux/
cd /usr/src/linux
make -j6 -l6 && make modules_install && make install

echo "sys-kernel/installkernel dracut" >> /etc/portage/package.use/installkernel
emerge sys-kernel/installkernel

#bootloader
echo 'GRUB_PLATFORMS="efi-64"' >> /etc/portage/make.conf
emerge grub
grub-install --efi-directory=/efi
grub-mkconfig -o /boot/grub/grub.cfg
