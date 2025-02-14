#!/bin/bash
wp_path=$HOME/papes
image=$(find "$wp_path" -type f \( -iname '*.jpg' -o -iname '*.jpeg' -o -iname '*.png' \) | shuf -n 1)
echo "$image"
swww img "$image"
