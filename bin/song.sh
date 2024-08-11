#!/bin/sh

title=$(playerctl -p spotify metadata title 2>/dev/null)
artist=$(playerctl -p spotify metadata artist 2>/dev/null)

if [ $? -ne 0 ]; then # spotify not running
    title=$(playerctl metadata title 2>/dev/null)
    artist=$(playerctl metadata artist 2>/dev/null)
    if [ $? -ne 0 ]; then
        exit 1
    elif [ "$artist" != "" ]; then
        echo -n "  $artist · $title"
    else
        echo -n "  $title"
    fi
elif [ "$artist" != "" ]; then
    echo -n "  $artist · $title"
elif [ "$title" != "" ]; then
    echo -n "  $title"
else  # spot not running
    exit 1
fi

