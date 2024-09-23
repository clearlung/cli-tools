#!/bin/sh

user=$(whoami)
read -r hostname < /etc/hostname
read -r host < /sys/devices/virtual/dmi/id/product_name
kernel=$(uname -r)

IFS=. read -r s _ < /proc/uptime
h=$((s / 60 / 60 % 24))
m=$((s / 60 % 60))

main () {
  echo "$user@$hostname"
  echo "-----------"
  echo "host: $host"
  echo "kernel: $kernel"
  echo "uptime: ${h}:${m}"
  printf "packages: "
  printf '%s\n' /var/db/pkg/*/*/ | wc -l
}

main "$@"
