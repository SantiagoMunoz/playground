#
# bashrc 
#

function mkcdir() {
  mkdir -p -- "$1" &&
    cd -P -- "$1"
}

alias prettyxml='xmllint --format - '
alias kastocao='prev=$(fc -ln | tail -2 | head -1);gdb --args $prev'
alias shin_count_lines='git ls-files | xargs cat | wc -l'
alias smake='make clean;clear;clear;make'
alias ttag='ctags -R .'
alias ll='ls -l'
alias la='ls -la'
alias gohome='shutdown now'
alias automount='udiskie --tray --use-udisks2'

#Default apps
export BROWSER=firefox
export EDITOR=vim

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '
