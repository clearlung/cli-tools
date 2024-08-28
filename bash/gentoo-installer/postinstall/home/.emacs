(require 'package)
(add-to-list 'package-archives '("melpa" . "https://melpa.org/packages/") t)
(package-initialize)

(custom-set-variables
 '(custom-safe-themes
   '("0f76f9e0af168197f4798aba5c5ef18e07c926f4e7676b95f2a13771355ce850" default))
 '(package-selected-packages '(slime)))

(setq-default indent-tabs-mode nil)
(setq-default tab-width 2)
(setq indent-line-function 'insert-tab)
(load-theme 'modus-vivendi)
(setq inferior-lisp-program "sbcl --core /usr/lib64/sbcl/sbcl.core")
(setq auto-mode-alist
      (append '((".*\\.cl\\'" . lisp-mode))
              auto-mode-alist))
