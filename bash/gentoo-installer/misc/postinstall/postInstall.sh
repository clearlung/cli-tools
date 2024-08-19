dir=/gentoo-installer/misc/postinstall
read -rp "username: " user
useradd -mG users,wheel,audio,video -s /bin/bash $user
passwd $user

#install xorg
echo "x11-libs/libdrm video_cards_radeon" > /etc/portage/package.use/libdrm
echo "sys-auth/pambase elogind" > /etc/portage/package.use/pambase
emerge x11-libs/libX11 x11-libs/libXinerama x11-libs/libXft x11-base/xorg-server x11-drivers/xf86-video-fbdev x11-drivers/xf86-video-vesa

emerge app-admin/sudo
echo "%wheel ALL=(ALL:ALL) NOPASSWD: ALL" >> /etc/sudoers

mkdir -p /etc/X11/xorg.conf.d
cp $dir/xorg/00-keyboard.conf /etc/X11/xorg.conf.d/
mkdir -p /etc/X11/xkb/symbols
cp $dir/xorg/pc /etc/X11/xkb/symbols
sudo -u $user cp -R $dir/home/.* /home/$user

emerge sys-apps/dbus sys-auth/elogind 

rc-update add dbus default
rc-update add elogind default
rc-service dbus start
rc-service elogind start
