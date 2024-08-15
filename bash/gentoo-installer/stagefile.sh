rootDir=/mnt/gentoo
installerDir=/mnt/gentoo/gentoo-installer

chronyd -q
wget http://www.gtlib.gatech.edu/pub/gentoo/releases/amd64/autobuilds/current-stage3-amd64-hardened-openrc/stage3-amd64-hardened-openrc-20240811T170405Z.tar.xz
wget http://www.gtlib.gatech.edu/pub/gentoo/releases/amd64/autobuilds/current-stage3-amd64-hardened-openrc/stage3-amd64-hardened-openrc-20240811T170405Z.tar.xz.sha256
sha256sum -c stage3-*.sha256
rm stage3-*.sha256
read -rp "Proceed? [Y/N]: " answer

case $answer in
    [yY])
        mv stage3-*.tar.xz /mnt/gentoo
        tar xpvf /mnt/gentoo/stage3-*.tar.xz -C $rootDir --xattrs-include='*.*' --numeric-owner
        cp $installerDir/portage/make.conf $rootDir/etc/portage
        cp --dereference /etc/resolv.conf $rootDir/etc
        rm $rootDir/stage3-*.tar.xz
        ;;
    *)
        echo "Cancelled"
        exit
        ;;
esac

read -rp "arch-chroot $rootDir [Y/N]: " answer

case $answer in
  [yY])
    arch-chroot $rootDir
    ;;
  *)
    echo "Cancelled"
    exit
    ;;
esac
