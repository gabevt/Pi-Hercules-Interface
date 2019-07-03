import CarControl
import sys

CarControl.setup()

while True:
	x = raw_input("New Speed: ")
	y = raw_input("New Direction: ")	
	x = int(x)
	y = int(y)
	
	CarControl.setSpeed(x)
	CarControl.setDirection(y)
