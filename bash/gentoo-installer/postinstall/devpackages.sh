installerDir=/gentoo-installer

#opengl
emerge media-libs/glfw
emerge media-libs/libsdl2

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

cp $installerDir/gentoo/portage/accept/stumpwm /etc/portage/package.accept_keywords/stumpwm
emerge x11-wm/stumpwm
