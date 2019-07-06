# Pi-Hercules-Interface

These codes provide an interface so you can control a Skeleton Bot - 4WD Hercules Mobile Robotic Platform from a Raspberry Pi via Python and a RC transmitter via a switch or toggle. The idea of this was to facilitate the implementation of an AI in this kind of platform.


# Getting Started

Download the code CarControl.py to your Raspberry Pi and the Code.ino Arduino project to your local machine. For your Raspberry Pi you will require the library PiGPIO. For your Arduino you will need to download the libraries for this platform (you can get it from http://wiki.seeedstudio.com/Hercules_Dual_15A_6-20V_Motor_Controller/ ) and upload the code via Arduino to the microcontroller of the platform.
Wiring is as follows:
Pi GPIO 17 => D12 Hercules Board
Pi GPIO 18 => D13 Hercules Board
Controller Aux Channel (listener toggle) => D2 Hercules Board


# Usage

Once everything is wired up you can refer to the Usage.py code for a basic example on how to use the interface.


# Built With
## Software:
Arduino
Sublime Text 3
Python 3

## Hardware:
Hercules Dual 15A 6-20V Motor Controller (ATMega328 Controller)
Raspberry Pi 3B+


# Authors

Gabriel Valdez Topete


# Acknowledgments

Libraries from Seeed Studio where used to control the platfrom from the microcontroller
