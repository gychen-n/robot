#! /bin/bash
cd /home/robot
sh turn_right.sh
sleep 4
gnome-terminal -- sh stop.sh
sleep 1
sh forward.sh
sleep 8
gnome-terminal -- sh stop.sh
sleep 1
sh turn_left.sh
sleep 4
gnome-terminal -- sh stop.sh
exit 0
