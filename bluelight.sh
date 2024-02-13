#!/bin/bash
#
current_time=$(date +"%H%M")
if ((1800<=$current_time && $current_time<=2400)) || (($current_time>=0000 && $current_time<=0600)); then
	xrandr --output HDMI-0 --brightness 0.35
	redshift -O 2000
else
	xrandr --output HDMI-0 --brightness 1	
	redshift -x	
fi



