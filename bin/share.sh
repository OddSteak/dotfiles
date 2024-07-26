#!/bin/bash
file=$(find $HOME -type f | dmenu -i -l 25)
curl -F "file=@$file" http://0x0.st | tr -d '\n' | xclip -selection c && notify-send "file uploaded" 
