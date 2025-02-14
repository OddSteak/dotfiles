# If you come from bash you might have to change your $PATH.
export PATH=$HOME/bin:$HOME/.local/bin:/usr/local/bin:$PATH

# Path to your Oh My Zsh installation.
export ZSH="$HOME/.oh-my-zsh"

# Set name of the theme to load --- if set to "random", it will
# load a random theme each time Oh My Zsh is loaded, in which case,
# to know which specific one was loaded, run: echo $RANDOM_THEME
# See https://github.com/ohmyzsh/ohmyzsh/wiki/Themes
ZSH_THEME="robbyrussell"

# Set list of themes to pick from when loading at random
# Setting this variable when ZSH_THEME=random will cause zsh to load
# a theme from this variable instead of looking in $ZSH/themes/
# If set to an empty array, this variable will have no effect.
# ZSH_THEME_RANDOM_CANDIDATES=( "robbyrussell" "agnoster" )

# Uncomment the following line to use case-sensitive completion.
# CASE_SENSITIVE="true"

# Uncomment the following line to use hyphen-insensitive completion.
# Case-sensitive completion must be off. _ and - will be interchangeable.
HYPHEN_INSENSITIVE="true"

# Uncomment one of the following lines to change the auto-update behavior
# zstyle ':omz:update' mode disabled  # disable automatic updates
zstyle ':omz:update' mode auto      # update automatically without asking
# zstyle ':omz:update' mode reminder  # just remind me to update when it's time

# Uncomment the following line to change how often to auto-update (in days).
zstyle ':omz:update' frequency 13

# Uncomment the following line if pasting URLs and other text is messed up.
# DISABLE_MAGIC_FUNCTIONS="true"

# Uncomment the following line to disable colors in ls.
# DISABLE_LS_COLORS="true"

# Uncomment the following line to disable auto-setting terminal title.
# DISABLE_AUTO_TITLE="true"

# Uncomment the following line to enable command auto-correction.
# ENABLE_CORRECTION="true"

# Uncomment the following line to display red dots whilst waiting for completion.
# You can also set it to another string to have that shown instead of the default red dots.
# e.g. COMPLETION_WAITING_DOTS="%F{yellow}waiting...%f"
# Caution: this setting can cause issues with multiline prompts in zsh < 5.7.1 (see #5765)
COMPLETION_WAITING_DOTS="true"

# Uncomment the following line if you want to disable marking untracked files
# under VCS as dirty. This makes repository status check for large repositories
# much, much faster.
# DISABLE_UNTRACKED_FILES_DIRTY="true"

# Uncomment the following line if you want to change the command execution time
# stamp shown in the history command output.
# You can set one of the optional three formats:
# "mm/dd/yyyy"|"dd.mm.yyyy"|"yyyy-mm-dd"
# or set a custom format using the strftime function format specifications,
# see 'man strftime' for details.
# HIST_STAMPS="mm/dd/yyyy"

# Would you like to use another custom folder than $ZSH/custom?
# ZSH_CUSTOM=/path/to/new-custom-folder

# Which plugins would you like to load?
# Standard plugins can be found in $ZSH/plugins/
# Custom plugins may be added to $ZSH_CUSTOM/plugins/
# Example format: plugins=(rails git textmate ruby lighthouse)
# Add wisely, as too many plugins slow down shell startup.
plugins=(
    gitignore
    tldr
    tmux
    command-not-found
    copybuffer
    copyfile
    copypath
    zsh-autosuggestions
)

source $ZSH/oh-my-zsh.sh

# User configuration

# export MANPATH="/usr/local/man:$MANPATH"

# You may need to manually set your language environment
# export LANG=en_US.UTF-8

# Preferred editor for local and remote sessions
if [[ -n $SSH_CONNECTION ]]; then
  export EDITOR='vim'
else
  export EDITOR='nvim'
fi

# Compilation flags
# export ARCHFLAGS="-arch $(uname -m)"

# Set personal aliases, overriding those provided by Oh My Zsh libs,
# plugins, and themes. Aliases can be placed here, though Oh My Zsh
# users are encouraged to define aliases within a top-level file in
# the $ZSH_CUSTOM folder, with .zsh extension. Examples:
# - $ZSH_CUSTOM/aliases.zsh
# - $ZSH_CUSTOM/macos.zsh
# For a full list of active aliases, run `alias`.
#

# The following lines were added by compinstall

zstyle ':completion:*' completer _expand _complete _ignored _approximate
zstyle ':completion:*' matcher-list '+m:{[:lower:]}={[:upper:]} m:{[:lower:][:upper:]}={[:upper:][:lower:]} r:|[._-/]=** r:|=**' '+r:|[._-/]=** r:|=** l:|=*'
zstyle :compinstall filename '/home/dell/.zshrc'

autoload -Uz compinit
compinit
# End of lines added by compinstall
# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=10000
SAVEHIST=20000
setopt autocd beep extendedglob nomatch notify
# End of lines configured by zsh-newuser-install


# HISTORY
setopt EXTENDED_HISTORY          # Write the history file in the ':start:elapsed;command' format.
setopt HIST_EXPIRE_DUPS_FIRST    # Expire a duplicate event first when trimming history.
setopt HIST_IGNORE_DUPS          # Do not record an event that was just recorded again.
setopt HIST_IGNORE_SPACE         # Do not record an event starting with a space.
setopt SHARE_HISTORY             # Share history between all sessions.
# END HISTORY

# convinience
alias c=clear
alias e=exit
alias dstatus='sudo systemctl status'
alias denable='sudo systemctl enable --now'
alias dstart='sudo systemctl start'

alias ll='ls -AalF'
alias la='ls -A'
alias l='ls -CF'

# programs
alias gs='git status'
alias ga='git add .'
alias gc='git commit -m'
alias g="git"
alias lg="lazygit"
alias wman=w3mman
alias py=python

# functions
jnc() {
    cd ~/uwa/sem2_2024/cits2402
    jupyter-notebook
}

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
        filep=$(find -L . \( -type f -o -type l \) | fzf -i | sed 's/^..//' | tr -d '\n')
    else
        filep=$(find -L "$1/" \( -type f -o -type l \) | fzf -i | tr -d '\n')
  fi
  echo -n \"$filep\" | wl-copy
  unset filep
}

mkcd() {
	mkdir -p "$1/" && cd "$1" || return
}

fshare() {
  if [ $# -eq 0 ]
    then
	  curl -F"file=@$(find ./ -type f | fzf -i)" http://0x0.st | wl-copy
    else
	  curl -F"file=@$(find "$1/" -type f | fzf -i)" http://0x0.st | tr -d '\n' | wl-copy
  fi
}


share() {
  if [ $# -eq 0 ]
    then
	  fshare
    else
	  curl -F"file=@$1" http://0x0.st | tr -d '\n' | wl-copy
  fi
}

fpatch() {
  fontforge --script ~/.config/fontpatcher/font-patcher --complete "$1"
}

zat() {
  zathura "$1" &!
}

rebar() {
    killall waybar; waybar &!
}
jconvert() {
    jupyter nbconvert --no-prompt --to script "$1"
}

eval $(thefuck --alias)

# ssh-agent
export SSH_AUTH_SOCK="$XDG_RUNTIME_DIR/ssh-agent.socket"

# pyenv
export PYENV_ROOT="$HOME/.pyenv"
[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"
eval "$(pyenv init - zsh)"
