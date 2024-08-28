#!/bin/bash
file="$(find "$HOME" -type f -not -path "$HOME/.pyenv/*" -not -path "$HOME/.vim/*" -not -path "$HOME/.mozilla/*" -not -path "$HOME/.qt_material/*" -not -path "$HOME/.m2/*" -not -path "$HOME/.cache/*" -not -path "$HOME/.local/*" -not -path "*/.venv/*" -not -path "*/.git/*" -not -path "$HOME/R/*" -not -path "$HOME/go/*" -not -path "$HOME/.oh-my-zsh/*" -not -path "$HOME/dev/qmk_wireless/lib/*" | rofi -dmenu -i)"
stripped_name=$(basename "$file")
url=$(curl -F "file=@$file" http://0x0.st | tr -d '\n' )
echo "$url"/"$stripped_name" | wl-copy && notify-send "file uploaded"
