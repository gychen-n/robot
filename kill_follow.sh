#! /bin/bash
echo "kill follow"
ps -ef | grep "follower" | grep -v grep | awk '{print $2}' | xargs kill -9
