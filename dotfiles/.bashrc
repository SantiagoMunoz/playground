#
# bashrc 
#

function mkcdir() {
  mkdir -p -- "$1" &&
    cd -P -- "$1"
}

alias prettyxml='xmllint --format - '
alias kastocao='prev=$(fc -ln | tail -2 | head -1);gdb --args $prev'
alias smake='make clean;clear;clear;make'
alias ll='ls -l'
alias la='ls -la'

alias automount='udiskie --tray --use-udisks2'

#Default apps
export BROWSER=firefox
export EDITOR=vim

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '
alias tmux="TERM=rxvt-unicode-256color tmux"

# vi mode!
set -o vi
