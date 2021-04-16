#!/bin/bash
cd /home/robot/face
rm -rf *.jpg *.pdf
cp /home/robot/face/bak/* /home/robot/face
cd /home/robot/HWFace/
python3 clear.py
