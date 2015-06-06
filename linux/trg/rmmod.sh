#!/usr/bin/env bash

NAME=modice
DEV="$NAME"_dev

# remove device
rmmod "$NAME"
rm /dev/"$DEV"

# show log
dmesg | tail -n 20