#! /bin/sh
echo "kill demo_revo_lds.launch"
pid=`ps -ef |grep "demo_revo_lds.launch"| head -1| awk '{print $2;}'`
echo  $pid
if [ "$pid" ]
then
	kill -TERM $pid
fi
echo "kill xiaoqiang_rslidar.launch"
pid2=`ps -ef |grep "xiaoqiang_rslidar.launch"| head -1| awk '{print $2;}'`
echo  $pid2
if [ "$pid2" ]
then
	kill -TERM $pid2
fi
echo "kill rs_lidar_16.launch"
pid3=`ps -ef |grep "rs_lidar_16.launch"| head -1| awk '{print $2;}'`
echo  $pid3
if [ "$pid3" ]
then
	kill -TERM $pid3
fi
echo "kill imu.launch"
pid4=`ps -ef |grep "imu.launch"| head -1| awk '{print $2;}'`
echo  $pid4
if [ "$pid4" ]
then
	kill -TERM $pid4
fi

#6w
#
#echo "kill stim.launch"
#pid4=`ps -ef |grep "stim.launch"| head -1| awk '{print $2;}'`
#echo  $pid4
#if [ "$pid4" ]
#then
#	kill -TERM $pid4
#fi









