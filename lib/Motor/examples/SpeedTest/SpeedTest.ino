/* Library to control CC motors with an H-bridge
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno for @ProyectoSirena
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	21/01/2015
*/

/* SpeedTest example:
*  Test the speed change in one motor with a potentiometer.
*/

#include <Motor.h>

//Arduino pins
#define pin_1 7
#define pin_2 8
#define pin_en 9
#define pot_pin 0

Motor m(pin_1,pin_2,pin_en);

int speed = 0;

void setup(){
	m.set_speed(speed);
	Serial.begin(115200);
}

void loop(){
	speed = map(analogRead(pot_pin),0,1023,0,255);
	Serial.print("Speed: ");
	Serial.println(speed);
	m.right(speed);

	delay(50);
}