/* Library to control CC motors with an H-bridge
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno for @ProyectoSirena
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	21/01/2015
*/

/* SingleTest example:
*  Test one motor going right and left.
*/

#include <Motor.h>

//Arduino pins
#define pin_1 7
#define pin_2 8
#define pin_en 9

Motor m(pin_1,pin_2,pin_en);

void setup(){
	m.set_speed(255);
	Serial.begin(115200);
}

void loop(){
	Serial.println("Right!");
	m.right();
	delay(1000);
	Serial.println("Stop!");
	m.stop();
	delay(1000);
	Serial.println("Left!");
	m.left();
	delay(1000);
	Serial.println("Stop!");
	m.stop();
	delay(2000);
}