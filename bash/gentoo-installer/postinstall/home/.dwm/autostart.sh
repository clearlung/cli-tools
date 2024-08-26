#!/bin/bash
#
gentoo-pipewire-launcher &
slstatus &
xmodmap -e "keycode 108 = Alt_R"
xmodmap -e "keycode 135 = Super_R"
xdotool mousemove 1920 1080
