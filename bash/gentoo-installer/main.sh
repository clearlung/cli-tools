export rootDir=/
export installerDir=/gentoo-installer
export editor=vi
export kernel=sys-kernel/vanilla-sources
export region=America

read -sp "start? [Y/N]: " answer
case $answer in
  [Yy])
    sh installBase.sh
    ;;
  *)
    exit
    ;;
esac

read -sp "continue? [Y/N]: " answer
case $answer in
  [Yy])
    sh kernel.sh
    ;;
  *)
    exit
    ;;
esac

read -sp "continue? [Y/N]: " answer
case $answer in
  [Yy])
    sh sysconfig.sh
    ;;
  *)
    exit
    ;;
esac
