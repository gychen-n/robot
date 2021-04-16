#!/bin/bash
cd /home/robot/face
convert -fill red -pointsize 50 -font helvetica -draw 'text 10,80 "Kevin" '  Kevin.jpg pdf1.jpg
convert -fill red -pointsize 50 -font helvetica -draw 'text 10,80 "jack" '  jack.jpg pdf2.jpg
convert -fill red -pointsize 50 -font helvetica -draw 'text 10,80 "lucy" '  lucy.jpg pdf3.jpg
convert pdf*.jpg output.pdf
