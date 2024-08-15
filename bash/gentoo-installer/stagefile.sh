dir=/mnt/gentoo/gentoo-installer

chronyd -q
wget http://www.gtlib.gatech.edu/pub/gentoo/releases/amd64/autobuilds/current-stage3-amd64-hardened-openrc/stage3-amd64-hardened-openrc-20240811T170405Z.tar.xz
wget http://www.gtlib.gatech.edu/pub/gentoo/releases/amd64/autobuilds/current-stage3-amd64-hardened-openrc/stage3-amd64-hardened-openrc-20240811T170405Z.tar.xz.sha256
sha256sum -c stage3-*.sha256
rm stage3-*.sha256
read -sp "Proceed? [Y/N]: " answer

case $answer in
	Y|y)
    mv stage3-*.tar.xz /mnt/gentoo
		tar xpvf /mnt/gentoo/stage3-*.tar.xz /mnt/gentoo --xattrs-include='*.*' --numeric-owner
    cp $dir/portage/make.conf /mnt/gentoo/etc/portage
    cp --dereference /etc/resolv.conf /mnt/gentoo/etc
    rm stage3-*.tar.xz
    ;;
	*)
    echo "Cancelled"
    rm stage3-*.tar.xz
    exit
    ;;
esac

read -sp "arch-chroot /mnt/gentoo [Y/N]: " answer
  
case $answer in 
  Y|y) 
    arch-chroot /mnt/gentoo
    ;;
  *)
    echo "Cancelled"
    exit
    ;;
esac
