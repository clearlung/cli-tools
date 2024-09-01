installerDir=/gentoo-installer

#opengl
emerge media-libs/glfw

echo "media-libs/freetype harfbuzz" >>  /etc/portage/package.use/sdl2
emerge media-libs/sdl2-image media-libs/sdl2-ttf media-libs/libsdl2

#lisp
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
