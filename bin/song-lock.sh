#!/bin/sh

title=$(playerctl metadata title 2>/dev/null)
artist=$(playerctl metadata artist 2>/dev/null)

if [[ $? == 1 ]]; then
    exit 1
elif [[ $artist != "" ]]; then
    echo -n "  $artist · $title"
else
    echo -n "  $title"
fi

