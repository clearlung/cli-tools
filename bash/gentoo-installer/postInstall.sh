#x11
echo "x11-libs/libdrm video_cards_radeon" > /etc/portage/package.use/libdrm
echo "sys-auth/pambase elogind" > /etc/portage/package.use/pambase
emerge libX11 libXinerama libXft xorg-server xmodmap x11-drivers/xf86-video-fbdev xf86-video-vesa
#misc
emerge app-editors/neovim app-shells/fzf app-misc/ranger app-misc/fastfetch
emerge net-misc/curl net-misc/yt-dlp dev-vcs/git
emerge app-admin/doas htop dbus elogind
#audio
echo "media-video/pipewire sound-server" > /etc/portage/package.use/pipewire
echo "media-video/pulseaudio daemon" >> /etc/portage/package.use/pipewire
emerge media-video/wireplumber media-video/pipewire media-libs/libpulse media-sound/pavucontrol 
#video
emerge media-video/ffmpeg media-video/mpv media-gfx/scrot media-gfx/sxiv
#net
echo "dev-python/PyQt6 qml opengl webchannel" > /etc/portage/package.use/qutebrowser
echo "dev-qt/qtbase icu opengl" >> /etc/portage/package.use/qutebrowser
echo "dev-qt/qtdeclarative opengl" >> /etc/portage/package.use/qutebrowser
echo "dev-qt/qttools opengl" >> /etc/portage/package.use/qutebrowser
echo "dev-qt/qttranslations opengl" >> /etc/portage/package.use/qutebrowser
echo "www-client/qutebrowser opengl" >> /etc/portage/package.use/qutebrowser
echo "dev-qt/qtwebengine opengl" >> /etc/portage/package.use/qutebrowser 
echo "dev-python/PyQt6-WebEngine opengl" >> /etc/portage/package.use/qutebrowser
echo "dev-libs/libxml2 icu" >> /etc/portage/package.use/qutebrowser
echo "sys-libs/zlib minizip" >> /etc/portage/package.use/qutebrowser
emerge www-client/qutebrowser
