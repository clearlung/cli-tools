command! W execute 'w !sudo tee % > /dev/null' <bar> edit!
syntax enable

set number
set background=dark
set nobackup
set nowb
set noswapfile
set expandtab
set smarttab
set shiftwidth=2
set tabstop=2

" Linebreak on 500 characters
set lbr
set tw=500

set ai "Auto indent
set si "Smart indent
set wrap "Wrap lines
