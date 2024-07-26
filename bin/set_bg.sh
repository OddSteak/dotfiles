#!/bin/bash
wp_path=$HOME/pics/papes/
image=$(ls $wp_path | grep -E '(jpg|png|jpeg)$' | shuf -n 1)
xwallpaper --zoom $wp_path/$image
