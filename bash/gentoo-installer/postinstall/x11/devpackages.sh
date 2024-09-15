installerDir=/gentoo-installer
user=blah

#opengl
emerge media-libs/glfw

printf "media-libs/freetype harfbuzz\n
        media-libs/sdl2-image png jpeg" >>  /etc/portage/package.use/sdl2

emerge media-libs/sdl2-image media-libs/sdl2-ttf media-libs/libsdl2

#lisp
emerge dev-lisp/sbcl
emerge dev-lisp/asdf

#python
emerge dev-python/pip

#java
emerge virtual/jdk virtual/jre

#lem
su -l $user

curl -L https://qlot.tech/installer | bash
echo 'export PATH=$HOME/.qlot/bin:$PATH"' >> $HOME/.bashrc
#mkdir $HOME/common-lisp && cd $HOME/common-lisp

git clone https://github.com/lem-project/lem.git .lem
cd .lem && make ncurses
echo 'export PATH="$HOME/.lem:$PATH"' >> $HOME/.bashrc
