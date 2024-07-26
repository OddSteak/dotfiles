#!/bin/sh

WP_ID="$(wpctl status | rg \(\\d\\d\).\ spotify\\s+$ -o --replace '$1')"

if [[ $1 == 'mute' ]]; then
    wpctl set-mute "$WP_ID" toggle
elif [[ $1 == 'inc' ]]; then
    wpctl set-volume "$WP_ID" 2%+
elif [[ $1 == 'dec' ]]; then
    wpctl set-volume "$WP_ID" 2%-
fi
