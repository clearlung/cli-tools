installerDir=/gentoo-installer

#misc
echo "permit nopass :wheel" > /etc/doas.conf
emerge app-editors/emacs app-editors/neovim app-shells/fzf app-misc/ranger app-misc/fastfetch net-misc/curl net-misc/yt-dlp dev-vcs/git sys-process/htop app-admin/doas x11-apps/xmodmap
#audio
echo "media-video/pipewire sound-server" > /etc/portage/package.use/pipewire
echo "media-video/pulseaudio daemon" >> /etc/portage/package.use/pipewire
emerge media-video/wireplumber media-video/pipewire media-libs/libpulse media-sound/pavucontrol 
#video
emerge media-video/ffmpeg media-video/mpv media-gfx/scrot media-gfx/sxiv
#net 
cp $installerDir/portage/use/qutebrowser /etc/portage/package.use
emerge dev-python/adblock www-client/qutebrowser net-p2p/qbittorrent

#other bullshit
emerge media-libs/mesa

emerge --no-replace app-eselect/eselect-repository
eselect repository enable steam-overlay
emaint -r steam-overlay sync

cp $installerDir/portage/use/steam /etc/portage/package.use/steam
echo "*/*::steam-overlay" > /etc/portage/package.accept_keywords/steam #should use multiline echo or just copy the file instead of calling echo 3 times
echo "games-util/game-device-udev-rules" >> /etc/portage/package.accept_keywords/steam
echo "sys-libs/libudev-compat" >> /etc/portage/package.accept_keywords/steam
echo "games-util/steam-launcher ValveSteamLicense" >> /etc/portage/package.license

emerge games-util/steam-launcher

echo "www-client/librewolf ~amd64" >> /etc/portage/package.accept_keywords/librewolf #same as comment above
echo "dev-libs/nss ~amd64" >> /etc/portage/package.accept_keywords/librewolf
eselect repository enable librewolf
emaint -r librewolf sync
emerge www-client/librewolf
