#! /bin/bash
gnome-terminal -- roscore
sleep 1
gnome-terminal -- bash ps3_connect.sh
sleep 20
gnome-terminal -- bash ps3fake.sh
sleep 1
