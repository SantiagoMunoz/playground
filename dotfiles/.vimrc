set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'scrooloose/nerdtree'
Plugin 'majutsushi/tagbar'
Plugin 'ctrlpvim/ctrlp.vim'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'enricobacis/vim-airline-clock'
Plugin 'vim-syntastic/syntastic'
Plugin 'colepeters/spacemacs-theme.vim'
Plugin 'tpope/vim-fugitive'
Plugin 'L9'
" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

" Configure vim-airline clock.
" No clock!
let g:airline#extensions#clock#format = ''
let g:airline_theme='alduin'

"spacemacs theme
if (has("termguicolors"))
    set termguicolors
endif
set background=dark
colorscheme default

" Syntax highlighting
syntax on
" Show line numbers
set number
" Line number color configuration
highlight LineNr ctermfg=white ctermbg=grey
" Tabs -> 4 spaces
set tabstop=4
set shiftwidth=4
set expandtab
" Make status bar always show
set laststatus=2

let g:syntastic_c_checkers = ['gcc']

" Map NerdTree and Tagbar to F keys
silent! map <F2> :NERDTreeToggle<CR>
silent! map <F3> :TagbarToggle<CR>

" Map escape to jk for convenience
inoremap jk <ESC>
" Syntax folding based on syntax
set foldmethod=syntax
" Highlight current search
set hlsearch
" Faster split navigation
map <C-l> <C-w>l
map <C-h> <C-w>h
map <C-k> <C-w>k
map <C-j> <C-w>j
map <C-/> : tab split<CR>:exec("tag ".expand("<cword>"))<CR>

" YCM from Arch AUR
let g:ycm_global_ycm_extra_conf = '/usr/share/vim/vimfiles/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py'
let g:ycm_server_python_interpreter = '/bin/python2.7'

