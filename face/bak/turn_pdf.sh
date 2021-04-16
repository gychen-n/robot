#!/bin/bash
cd /home/robot/face
convert -fill red -pointsize 50 -font helvetica -draw 'text 10,80 "person0" '  person0.jpg pdf1.jpg
convert -fill red -pointsize 50 -font helvetica -draw 'text 10,80 "person1" '  person1.jpg pdf2.jpg
convert -fill red -pointsize 50 -font helvetica -draw 'text 10,80 "person2" '  person2.jpg pdf3.jpg
convert pdf*.jpg output.pdf
