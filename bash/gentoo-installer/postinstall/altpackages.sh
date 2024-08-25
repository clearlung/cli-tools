installerDir=/gentoo-installer

#misc
echo "permit nopass :wheel" > /etc/doas.conf
emerge app-editors/vim app-shells/fzf app-misc/ranger app-misc/fastfetch net-misc/curl net-misc/yt-dlp dev-vcs/git sys-process/htop app-admin/doas x11-apps/xmodmap
#audio
echo "media-video/pipewire sound-server pipewire-alsa" > /etc/portage/package.use/pipewire
echo "media-video/pulseaudio daemon" >> /etc/portage/package.use/pipewire
emerge media-video/wireplumber media-video/pipewire media-libs/libpulse media-sound/pavucontrol
#video
emerge media-video/ffmpeg media-video/mpv media-gfx/scrot media-gfx/sxiv

emerge dev-lisp/sbcl
emerge dev-lisp/asdf
echo "(when (probe-file #p"/etc/common-lisp/gentoo-init.lisp")
    (load #p"/etc/common-lisp/gentoo-init.lisp"))" > .sbclrc

curl -L https://qlot.tech/installer | bash
echo 'export PATH=$HOME/.qlot/bin:$PATH"' >> $HOME/.bashrc
mkdir $HOME/common-lisp && cd $HOME/common-lisp
git clone https://github.com/lem-project/lem.git
cd lem && make ncurses
echo 'export PATH="$HOME/common-lisp/lem:$PATH"' >> $HOME/.bashrc

#this might be masked
emerge x11-wm/stumpwm
