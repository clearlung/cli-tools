#!/bin/bash
#
output=HDMI-0
current_time=$(date +"%H%M")
if ((1800<=$current_time && $current_time<=2400)) || (($current_time>=0000 && $current_time<=0600)); then
	xrandr --output $output --brightness 0.4 --gamma 1:0.2:0.2
else
	xrandr --output $output --brightness 1 --gamma 1:1:1	
fi



