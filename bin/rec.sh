ffmpeg -f x11grab -y -framerate 30 -s 1366x768 -i :1 -c:v libx264 -preset superfast -crf 18 out.mp4
