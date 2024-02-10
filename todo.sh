#!/bin/bash
#
list=~/projects/todo/list.txt
if [[ ${2} != '' ]]; then
	case ${1} in
		-n) echo ${2} >> $list;;
		-r) sed -i "$(grep -n ${2} $list | cut -d : -f 1)d" $list; echo Cookies for you!;;
		-fr) sed -i "$(grep -n ${2} $list | cut -d : -f 1)d" $list;;
	esac
else
	case ${1} in
		-n)
			read -p "Enter Task: "
			echo "$REPLY" >> $list;;
		-r) 
			cat $list
			read -p "Enter Task: "
			sed -i "$(grep -n "$REPLY" $list | cut -d : -f 1)d" $list
	       		echo Cookies for you!;;
		-fr) 
			cat $list
			read -p "Enter Task: "
			sed -i "$(grep -n "$REPLY" $list | cut -d : -f 1)d" $list;;
		*) cat $list;;
	esac
fi
