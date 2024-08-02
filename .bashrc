#
# ~/.bashrc
#

export PATH="/home/dell/bin:$PATH"

# themes
eval "$(starship init bash)"
export LS_COLORS="$(vivid generate catppuccin-mocha)"

shopt -s globstar
alias grep='grep --color=auto'
alias ls='ls --color=auto'

# convinience
alias c=clear
alias e=exit
alias dstatus='sudo systemctl status'

alias ll='ls -AalF'
alias la='ls -A'
alias l='ls -CF'

# programs
alias ff=fastfetch
alias gs='git status'
alias g="git"
alias lg="lazygit"
alias wman=w3mman


# functions
fvsd() {
  if [ $# -eq 0 ]
    then
      nvim "$(find . -type d | fzf -i)"
    else
      nvim "$(find "$1/" -type d | fzf -i)"
  fi
}

fnv() {
  if [ $# -eq 0 ]
    then
      nvim "$(find . -type f | fzf -i)"
    else
      nvim "$(find "$1/" -type f | fzf -i)"
  fi
}

fnvn() {
  echo -n "new filename: "
  read -r filen
  if [ $# -eq 0 ]
    then
      dir=$(find . -type d | fzf -i)
    else
      dir=$(find "$1/" -type d | fzf -i)
  fi

  nvim "$dir/$filen"
}

fcomp() {
	if [ $# -eq 0 ]
	  then
	    file1=$(find . -type f | fzf -i)
	    file2=$(find . -type f | fzf -i)
	  else
	    file1=$(find "$1/" -type f | fzf -i)
	    file2=$(find "$1/" -type f | fzf -i)
	fi

	git diff --no-index "$file1" "$file2"
}

fcd() {
  if [ $# -eq 0 ]
    then
      cd "$(find . -type d | fzf -i)" || return
    else
      cd "$(find "$1/" -type d | fzf -i)" || return
  fi
}

open() {
  if [ $# -eq 0 ]
    then
      xdg-open "$(find . -type f | fzf -i)"
    else
      xdg-open "$(find "$1/" -type f | fzf -i)"
  fi
}

getpath() {
  if [ $# -eq 0 ]
    then
      find . -type f | fzf -i | sed 's/^..//' | tr -d '\n' | clip.exe
    else
      find "$1/" -type f | fzf -i | tr -d '\n' | clip.exe
  fi
}

mkcd() {
	mkdir -p "$1/" && cd "$1" || return
}

fshare() {
  if [ $# -eq 0 ]
    then
	  curl -F"file=@$(find ./ -type f | fzf -i)" http://sedentaryowl.xyz/static | wl-copy
    else
	  curl -F"file=@$(find "$1/" -type f | fzf -i)" http://sedentaryowl.xyz/static | wl-copy
  fi
}


share() {
  if [ $# -eq 0 ]
    then
	  fshare
    else
	  curl -F"file=@$1" http://sedentaryowl.xyz/static | wl-copy
  fi
}

fpatch() {
  fontforge --script ~/.config/fontpatcher/font-patcher --complete "$1"
}

zat() {
    zathura "$1" &
}
