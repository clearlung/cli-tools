#these steps can be skipped using installkernel with grub use flag
grub-install --efi-directory=/efi
grub-mkconfig -o /boot/grub/grub.cfg

#now exit and reboot
