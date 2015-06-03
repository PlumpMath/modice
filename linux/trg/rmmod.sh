#!/usr/bin/env bash

NAME=ku_pir
DEV="$NAME"_dev

# remove device
rmmod "$NAME"
rm /dev/"$DEV"

# show log
tail -f /var/log/messages -n 40