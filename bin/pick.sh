COL=$(hyprpicker)

hyprctl notify 1 5000 0 "fontsize:15  color $COL copied to clipboard"

echo $COL | wl-copy
