#!/bin/sh

artist=$(playerctl metadata artist 2>/dev/null)
title=$(playerctl metadata title 2>/dev/null)

if [[ $? == 1 ]]
then
    exit 1
else
    echo -n "  $title · $artist"
fi

