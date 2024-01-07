Formula Electric 

SPI - Using the Arduino as a Slave

Description:
Uses an arduino and an ultrasonic sensor to send a distance value through SPI to the STM32 which then turns on an LED with a PWM signal depending on the distance.

Required Hardware:
-STM32 NUCLEO-F767ZI 
-Arduino Uno
-Ultrasonic Sensor (HC-SR04)
-LED

STM32 Pins:
- SPI 
	- SCK: PE_2
	- CS: PE_4
	- MISO: PE_5
	- MOSI: PE_6
-Timer
	- PWM (for LED): PE_9

Arduino Pins (digital):
- SPI
	- SCK: 13
	- MISO: 12
	- MOSI: 11
	- CS: 10
	- GPIO (value received from STM32 = LED ON): 7
- Ultrasonic Sensor
	- Trig: 5
	- Echo: 6

Instructions: 
- Connect associated SPI lines on the STM32 with the Arduino
- Setup an LED connected to the PWM line of the STM32
- Setup ultrasonic sensor with appropriate connections to the arduino
- (optional) Setup an LED connected to channel 7 of the Arduino
- Upload code on both the Arduino and the STM32


 
