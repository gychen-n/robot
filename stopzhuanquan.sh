#! /bin/bash
pid1=`ps -ef |grep "turn_left"| head -1| awk '{print $2;}'`
echo  $pid1
if [ "$pid1" ]
then
	kill -TERM $pid1
fi
