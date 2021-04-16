#!/usr/bin/env python2
import cv2
import time
cap = cv2.VideoCapture(2)
#while(1):
    # get a frame
#time.sleep(2)
ret, frame = cap.read()
    # show a frame
cv2.imshow("capture", frame)
    #if cv2.waitKey(1) & 0xFF == ord('q'):
time.sleep(1)
cv2.imwrite("/home/robot/face/name.jpg", frame)

   # break
cap.release()
cv2.destroyAllWindows()
