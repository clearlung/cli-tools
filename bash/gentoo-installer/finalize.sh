user=clear

useradd -mG users,wheel,audio,video -s /bin/bash $user
passwd $user
