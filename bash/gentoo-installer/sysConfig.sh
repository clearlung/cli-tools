editor=nano
bootPartition=/dev/blah
rootPartition=/dev/blah
homePartition=/dev/blah

echo "$rootPartition  / ext4  defaults  0 1" >> /etc/fstab
echo "$bootPartition  /efi  vfat  defaults  1 2" >> /etc/fstab
echo "$homePartition  /home ext4  defaults  0 2" >> /etc/fstab

read -sp "hostname: " hostname
echo $hostname > /etc/hostname

passwd
$editor /etc/conf.d/keymaps
