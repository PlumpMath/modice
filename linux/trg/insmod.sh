#!/usr/bin/env sh

NAME=modice
#APP="$NAME"_app
DEV="$NAME"_dev

# insert driver
insmod "$NAME".ko

#MAJOR=$(cat /proc/devices | grep -oP "[0-9]+(?= $DEV)") #o for print match-char-only, P for PCRE match
MAJOR=$(awk "\$2==\"$DEV\" {print \$1}" /proc/devices)

mknod /dev/"$DEV" c "$MAJOR" 0

# set owner and run application
#chmod 777 "$APP"
#chown root "$APP"
#./"$APP"