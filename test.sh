#!/bin/bash
#
currentDate=$(date +%d)
currentTime=$(date +%H:%M)
function journal {
	if test -f "~/shortcuts/journal/$currentDate"; then
		echo -e "\n$currentTime" >> ~/shortcuts/journal/$currentDate
		vim ~/shortcuts/journal/$currentDate
	else
		touch ~/shortcuts/journal/$currentDate
		journal
	fi
}
journal
