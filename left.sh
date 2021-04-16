#! /bin/bash
cd /home/robot
sh forward.sh
sleep 3.5
gnome-terminal -- sh stop.sh
sleep 1
exit 0
