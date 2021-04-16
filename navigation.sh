#! /bin/bash
cd ~
source ~/batkin/devel_isolated/setup.bash
#gnome-terminal -- bash driver.sh
#sleep 1
gnome-terminal -- bash imu.sh
sleep 1
gnome-terminal -- bash lidar.sh 
sleep 1
gnome-terminal -- bash 3to2.sh 
sleep 1
gnome-terminal -- bash start_navigation.sh 
sleep 1
gnome-terminal -- bash add_waypoint.sh
sleep 1

