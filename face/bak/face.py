#coding=utf-8
import face_recognition
import cv2
import numpy as np
import os
import time
f = open('/home/robot/face/face_person','r')
line=f.read()
f.close
line=line.strip('\n')
print line
# This is a demo of running face recognition on live video from your webcam. It's a little more complicated than the
# other example, but it includes some basic performance tweaks to make things run a lot faster:
#   1. Process each video frame at 1/4 resolution (though still display it at full resolution)
#   2. Only detect faces in every other frame of video.

# PLEASE NOTE: This example requires OpenCV (the `cv2` library) to be installed only to read from your webcam.
# OpenCV is *not* required to use the face_recognition library. It's only required if you want to run this
# specific demo. If you have trouble installing it, try any of the other demos that don't require it instead.

# Get a reference to webcam #0 (the default one)
video_capture = cv2.VideoCapture(0)
#f = open('/home/robot/face_state','w')
#f.write('open')
#f.close
person0_image = face_recognition.load_image_file("person0.jpg")
person0_face_encoding = face_recognition.face_encodings(person0_image)[0]

# Load a second sample picture and learn how to recognize it.
person1_image = face_recognition.load_image_file("person1.jpg")
person1_face_encoding = face_recognition.face_encodings(person1_image)[0]

# Load a second sample picture and learn how to recognize it.
person2_image = face_recognition.load_image_file("person2.jpg")
person2_face_encoding = face_recognition.face_encodings(person2_image)[0]

# Create arrays of known face encodings and their names
known_face_encodings = [
    person0_face_encoding,
    person1_face_encoding,
	person2_face_encoding
]
known_face_names = [
    "person0",
    "person1",
    "person2"
]
times=0
flag=0
stopflag=0
locflag=1
count=0
t=0
# Initialize some variables
face_locations = []
face_encodings = []
face_names = []
process_this_frame = True

while True:
    # Grab a single frame of video
    ret, frame = video_capture.read()

    # Resize frame of video to 1/4 size for faster face recognition processing
    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)

    # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
    rgb_small_frame = small_frame[:, :, ::-1]
    
    # Only process every other frame of video to save time
    if process_this_frame:
	
        # Find all the faces and face encodings in the current frame of video
        face_locations = face_recognition.face_locations(rgb_small_frame)
        face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)
	flag=0
        face_names = []
        for face_encoding in face_encodings:
            # See if the face is a match for the known face(s)
            matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
            name = "Unknown"
            
	    flag=1
	    if count is not 0:
		count=count-1
		print count
		continue
	    
            # # If a match was found in known_face_encodings, just use the first one.
            # if True in matches:
            #     first_match_index = matches.index(True)
            #     name = known_face_names[first_match_index]

            # Or instead, use the known face with the smallest distance to the new face
            face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
            best_match_index = np.argmin(face_distances)
		
            if matches[best_match_index]:
                name = known_face_names[best_match_index]
		print name
		#print times
		
		if name==line:
			
			stopflag=1 #停止
			
			n=os.system("sh /home/robot/stop.sh")#停止
			time.sleep(2)
			#n=os.system("sh /home/robot/kill_all_action.sh")#杀死进程
			f = open('/home/robot/face_state','w')
			f.write('exit')
			f.close
			#n=os.system("sh /home/robot/kill_all_action.sh")#杀死进程
			exit()
		else :
			stopflag=1

			if locflag==1:
				#times=101
				n=os.system("sh /home/robot/stop.sh")#停止
				time.sleep(1)
				print "left"
				n=os.system("sh /home/robot/left.sh")#左转前进右转
				t=0;
				count=5
				#print n
				locflag=2
				#n=os.system("sh /home/robot/kill_all_action.sh &")#杀死进程
			elif locflag==2:
				n=os.system("sh /home/robot/stop.sh")#停止
				time.sleep(1)
				print "right"
				n=os.system("sh /home/robot/left.sh ")#右转前进左转
				t=0;
				locflag=3
		
            face_names.append(name)

    process_this_frame = not process_this_frame
    
    if flag == 0 and t==0 and stopflag==0:#未找到人脸
   		print "no" 
		t=1
		print "forward"
		n=os.system("sh /home/robot/forward.sh")#前进
		#n=os.system("sh /home/robot/kill_all_action.sh")#杀死进程
		#n=os.system("sh /home/robot/stop.sh")#停止
		#n=os.system("sh /home/robot/kill_all_action.sh")#杀死进程
    if flag==0:
		times=times+1
		#print times	
		
    #else:
		#print "stop"
		
		#if stopflag==1:
			#n=os.system("sh /home/robot/stop.sh")#停止
			#n=os.system("sh /home/robot/kill_all_action.sh")#杀死进程
			#a=0
    # if times>100:
	# n=os.system("sh /home/robot/stop.sh")#停止
	# time.sleep(2)
	# #n=os.system("sh /home/robot/kill_all_action.sh")#杀死进程
	# f = open('/home/robot/face_state','w')
	# f.write('exit')
	# f.close
	# 		#n=os.system("sh /home/robot/kill_all_action.sh")#杀死进程
	# exit()
    # Display the results
    for (top, right, bottom, left), name in zip(face_locations, face_names):
        # Scale back up face locations since the frame we detected in was scaled to 1/4 size
        top *= 4
        right *= 4
        bottom *= 4
        left *= 4

        # Draw a box around the face
        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)

        # Draw a label with a name below the face
 	cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)

    # Display the resulting image
    cv2.imshow('Video', frame)

    # Hit 'q' on the keyboard to quit!
    if cv2.waitKey(1) & 0xFF == ord('q'):
	n=os.system("sh /home/robot/kill_all_action.sh")#杀死进程
        break

# Release handle to the webcam
video_capture.release()
cv2.destroyAllWindows()
