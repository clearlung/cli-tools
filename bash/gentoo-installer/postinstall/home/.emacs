(require 'package)
(add-to-list 'package-archives '("melpa" . "https://melpa.org/packages/") t)
(package-initialize)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(custom-safe-themes
   '("0f76f9e0af168197f4798aba5c5ef18e07c926f4e7676b95f2a13771355ce850" default))
 '(inhibit-startup-screen t)
 '(package-selected-packages '(slime)))

(global-display-line-numbers-mode 1)

(setq-default indent-tabs-mode nil)
(setq-default tab-width 2)
(setq indent-line-function 'insert-tab)
(load-theme 'modus-vivendi)
(setq inferior-lisp-program "sbcl --core /usr/lib64/sbcl/sbcl.core")
(setq auto-mode-alist
      (append '((".*\\.cl\\'" . lisp-mode))
              auto-mode-alist))
(setq backup-directory-alist `(("." . "~/.saves")))

(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
