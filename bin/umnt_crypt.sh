#!/bin/sh
doas umount /dev/mapper/e1
doas cryptsetup close e1
