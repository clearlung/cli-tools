#no idea if this works
export rootDir=/
export installerDir=/gentoo-installer
export editor=vi
export kernel=sys-kernel/vanilla-sources
export region=America

read -sp "start? [Y/N]: " answer
case $answer in
  [Yy])
    bash installBase.sh
    ;;
  *)
    exit
    ;;
esac

read -sp "continue? [Y/N]: " answer
case $answer in
  [Yy])
    bash kernel.sh
    ;;
  *)
    exit
    ;;
esac

read -sp "continue? [Y/N]: " answer
case $answer in
  [Yy])
    bash sysconfig.sh
    ;;
  *)
    exit
    ;;
esac
