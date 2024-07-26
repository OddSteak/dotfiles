#!/bin/sh
doas cryptsetup open --type tcrypt /dev/nvme0n1p3 e1
doas mount --mkdir /dev/mapper/e1 /data
