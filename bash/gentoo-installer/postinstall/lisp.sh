emerge dev-lisp/sbcl
emerge dev-lisp/asdf
echo "(when (probe-file #p"/etc/common-lisp/gentoo-init.lisp")
    (load #p"/etc/common-lisp/gentoo-init.lisp"))" > .sbclrc
#emacs
emerge app-editors/emacs
#install slime
