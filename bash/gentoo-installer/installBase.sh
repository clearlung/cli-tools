#editor=vim
#region=America

emerge-webrsync
emerge --oneshot app-portage/mirrorselect
mirrorselect -io >> /etc/portage/make.conf
emerge --oneshot app-portage/cpuid2cpuflags
echo "*/* $(cpuid2cpuflags)" > /etc/portage/package.use/00cpu-flags

if [[ $editor == "vim" ]]; then
  emerge vim
  eselect editor list
  read -rp "number: " editornum
  eselect editor set $editornum
else if [[ $editor == "emacs" ]]; then
  emerge emacs
  eselect editor list
  read -rp "number: " editornum
  eselect editor set $editornum
else
  export editor=nano
fi

ls /usr/share/zoneinfo/$region
read -rp "city: " city
echo "$region/$city" > /etc/timezone
emerge --config sys-libs/timezone-data

$editor /etc/locale.gen
locale-gen
eselect locale list
read -rp "locale: " locale
eselect locale set $locale
. /etc/profile
