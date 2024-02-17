#!/bin/bash
#
PS3='Enter number: '
select song in ambience1 ambience2 ambience3 AmbientTracks BootlegTracks Loneliness_1A Powerline polyrhythm; do
	echo "Playing $song"
	find ~/Music/$song.flac | xargs mpv
done
