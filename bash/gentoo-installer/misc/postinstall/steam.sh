#!/bin/bash
#I haven't tested this script yet
installerDir=/gentoo-installer
emerge media-libs/mesa

emerge --no-replace app-eselect/eselect-repository
eselect repository enable steam-overlay
emaint sync -r steam-overlay

cp $installerDir/portage/use/steam /etc/portage/package.use/steam
echo "*/*::steam-overlay" > /etc/portage/package.accept_keywords/steam
echo "games-util/game-device-udev-rules" >> /etc/portage/package.accept_keywords/steam
echo "sys-libs/libudev-compat" >> /etc/portage/package.accept_keywords/steam
echo "games-util/steam]-launcher ValveSteamLicense" >> /etc/portage/package.license/steam

emerge games-util/steam-launcher
