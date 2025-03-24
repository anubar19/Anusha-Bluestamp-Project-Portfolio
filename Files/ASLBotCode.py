from picamera2 import Picamera2, Preview
import time
import numpy as np
from pynput import keyboard
import time
from adafruit_servokit import ServoKit

kit = ServoKit(channels=16)

picam2 = Picamera2()
picam2.start_preview(Preview.QTGL)
picam2.start()
print('camera started')
print('pipeline made')
captured_image = None
is_captured = False

'''
These are the functions for signing letters with the hand. Each finger
is represented by an index in the kit.servo object. (0 for the thumb, 1
for the pointer finger, 2 for the ring finger, 3 for the middle finger,
and 4 for the pinky finger)
'''
def show_hand():
    kit.servo[0].angle = 30
    kit.servo[1].angle = 180
    kit.servo[2].angle = 180
    kit.servo[3].angle = 180
    kit.servo[4].angle = 180
def show_B():
    kit.servo[0].angle = 180
    kit.servo[1].angle = 180
    kit.servo[2].angle = 180
    kit.servo[3].angle = 180
    kit.servo[4].angle = 180 

def show_C():
    kit.servo[0].angle = 120
    kit.servo[1].angle = 90
    kit.servo[2].angle = 90
    kit.servo[3].angle = 90
    kit.servo[4].angle = 90

def show_D():
    kit.servo[0].angle = 150
    kit.servo[1].angle = 180
    kit.servo[2].angle = 45
    kit.servo[3].angle = 45
    kit.servo[4].angle = 45

def show_E():
    kit.servo[0].angle = 180
    kit.servo[1].angle = 0
    kit.servo[2].angle = 0
    kit.servo[3].angle = 0
    kit.servo[4].angle = 0 

def show_F():
    kit.servo[0].angle = 150
    kit.servo[1].angle = 45
    kit.servo[2].angle = 180
    kit.servo[3].angle = 180
    kit.servo[4].angle = 180

def show_I():
    kit.servo[0].angle = 150
    kit.servo[1].angle = 45
    kit.servo[2].angle = 45
    kit.servo[3].angle = 45
    kit.servo[4].angle = 180

def show_L():
    kit.servo[0].angle = 20
    kit.servo[1].angle = 180
    kit.servo[2].angle = 0
    kit.servo[3].angle = 0
    kit.servo[4].angle = 0 

def show_O():
    kit.servo[0].angle = 120
    kit.servo[1].angle = 60
    kit.servo[2].angle = 60
    kit.servo[3].angle = 60
    kit.servo[4].angle = 60 

def show_U():
    kit.servo[0].angle = 180
    kit.servo[1].angle = 180
    kit.servo[2].angle = 180
    kit.servo[3].angle = 0
    kit.servo[4].angle = 0 

def show_X():
    kit.servo[0].angle = 180
    kit.servo[1].angle = 100
    kit.servo[2].angle = 0
    kit.servo[3].angle = 0
    kit.servo[4].angle = 0 

def show_Y():
    kit.servo[0].angle = 0
    kit.servo[1].angle = 0
    kit.servo[2].angle = 0
    kit.servo[3].angle = 0
    kit.servo[4].angle = 180

print("Press any key to capture an image. Press 'q' to quit.")

# Function to resize image
def resize_image(image, scale_percent):
    width = int(image.shape[1] * scale_percent / 100)
    height = int(image.shape[0] * scale_percent / 100)
    dim = (width, height)
    resized = cv2.resize(image, dim, interpolation=cv2.INTER_AREA)
    return resized

def on_press(key):
	global captured_image, is_captured
	try:
		if key.char == 'q':
			# Stop listener
			return False
		else:
			# Capture the image
			captured_image = picam2.capture_array()
			print("Image captured and saved as 'captured_image.npy'")
			captured_image = captured_image[:, :, :3]
			is_captured = True
			
			print('camera stopped')
			
	except AttributeError:
		# Handle special keys
		pass
	


# Start the listener in a separate thread
listener = keyboard.Listener(on_press=on_press)
listener.start()
'''
The rest of this code takes in the image captured in line 21, and passes it
through the text recognition process, which uses the keras_ocr library.
'''

import keras_ocr
import cv2
pipeline = keras_ocr.pipeline.Pipeline()

images = [resize_image(captured_image, 20)]

prediction_groups = pipeline.recognize(images=[images[0]])[0]

for text, box in prediction_groups:
	print('predicted text is: ',text)
	for char in text:
		print('Currently signing ', char)
		if char.upper() == "B":
			show_B()
			time.sleep(3)
		elif char.upper() == "C":
			show_C()
			time.sleep(3)
		elif char.upper() == "D":
			show_D()
			time.sleep(3)
		elif char.upper() == "E":
			show_E()
			time.sleep(3)
		elif char.upper() == "F":
			show_F()
			time.sleep(3)
		elif char.upper() == "I":
			show_I()
			time.sleep(3)
		elif char.upper() == "L":
			show_L()
			time.sleep(3)
		elif char.upper() == "O":
			show_O()
			time.sleep(3)
		elif char.upper() == "U":
			show_U()
			time.sleep(3)
		elif char.upper() == "X":
			show_X()
			time.sleep(3)
		elif char.upper() == "Y":
			show_Y()
			time.sleep(3)
		else:
			show_hand()
			time.sleep(3)
