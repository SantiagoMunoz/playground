set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

Plugin 'suoto/vim-hdl'
Plugin 'scrooloose/nerdtree'
Plugin 'ctrlpvim/ctrlp.vim'
Plugin 'Valloric/YouCompleteMe'		
Plugin 'vim-airline/vim-airline'
Plugin 'vim-syntastic/syntastic'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
Plugin 'L9'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

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
" NerdTree
silent! map <F2> :NERDTreeToggle<CR>
silent! map <F3> :NERDTreeFind<CR>

" Remap escape to jk for convenience
inoremap jk <ESC>
" Syntax folding based on syntax
set foldmethod=syntax
"highlight current search
set hlsearch
" Faster split navigation
map <C-l> <C-w>l
map <C-h> <C-w>h
map <C-k> <C-w>k
map <C-j> <C-w>j
map <C-/> : tab split<CR>:exec("tag ".expand("<cword>"))<CR>
