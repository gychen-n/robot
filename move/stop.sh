#! /bin/sh
pid1=`ps -ef |grep "turn_left"| head -1| awk '{print $2;}'`
echo  $pid1
if [ "$pid1" ]
then
	kill -TERM $pid1
fi

pid2=`ps -ef |grep "turn_right"| head -1| awk '{print $2;}'`
echo  $pid2
if [ "$pid2" ]
then
	kill -TERM $pid2
fi

pid3=`ps -ef |grep "forward"| head -1| awk '{print $2;}'`
echo  $pid3
if [ "$pid3" ]
then
	kill -TERM $pid3
fi
