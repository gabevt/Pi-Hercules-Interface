#sudo pigpiod
#1450-1550 Neutral, 1250 full backwards, 1750 full forward

import pigpio

pi = pigpio.pi()

def setup():
	#Initialize and put both speed and direction to neutral
	pi.set_servo_pulsewidth(17, 1500)
	pi.set_servo_pulsewidth(18, 1500)

def setSpeed(speed):
	#-100 = Full reverse
	#0 = Stationary
	#100 = Full forward	
	if speed>=-100 and speed<=100:#ignore invalid values
		speed = speed*2#Adjust to match timing 
		if speed==0:
			pi.set_servo_pulsewidth(17, 1500)
			#print "Adjusting speed PWM to: 1500",
		elif speed<0:
			pi.set_servo_pulsewidth(17, 1450+speed)
			#print "Adjusting speed PWM to: ",speed+1450
		elif speed>0:
			pi.set_servo_pulsewidth(17, 1550+speed)
			#print "Adjusting speed PWM to: ",1550+speed
			
def setDirection(direction):
	#100: Tight Right
	#50: Medium Right
	#0: Straight
	#-50: Medium Left
	#-100: Tight Left
	if direction>=-100 and direction<=100:
		direction = direction*2
		if direction==0:
			pi.set_servo_pulsewidth(18, 1500)
			#print "Adjusting direction PWM to: 1500",
		elif direction<0:
			pi.set_servo_pulsewidth(18, 1450+direction)
			#print "Adjusting direction PWM to: ",direction+1450
		elif direction>0:
			pi.set_servo_pulsewidth(18, 1550+direction)
			#print "Adjusting direction PWM to: ",1550+direction

def reset():
	setDirection(0)
	setSpeed(0)

	
