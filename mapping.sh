#! /bin/bash
gnome-terminal -- bash imu.sh
sleep 1
gnome-terminal -- bash lidar.sh 
sleep 1
gnome-terminal -- bash 3to2.sh 
sleep 1
gnome-terminal -- bash creat_map.sh 

