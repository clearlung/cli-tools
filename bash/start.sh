execute=1
browser="qutebrowser"
terminal="st"

function execute() {
  /usr/bin/$1 & disown
}

if [ "$1" = "b" ]; then
  execute $browser
elif [ "$1" = "t" ]; then
  execute $terminal
elif [ "$1" = "u" ]; then
  wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%+
elif [ "$1" = "d" ]; then
  wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%-
elif [ -n "$1" ]; then
  if ls /bin | grep -q "^$1$"; then
    execute $1
  else
    echo "/bin/$1 not found"
  fi
else
  printf "$ "
  read -r program
  execute $program
fi

