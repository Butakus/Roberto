/* Library to control CC motors with an H-bridge
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno for @ProyectoSirena
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	21/01/2015
*/

/* DualTest example:
*  Test two motors together. Loop going forward, backward and turning.
*/

#include <Motor.h>

//Arduino pins
#define pin_A1 7
#define pin_A2 8
#define pin_enA 9
#define pin_B1 10
#define pin_B2 11
#define pin_enB 12

Motor mA(pin_A1,pin_A2,pin_enA);
Motor mB(pin_B1,pin_B2,pin_enB);

void setup(){
	mA.set_speed(255);
	mB.set_speed(255);
	Serial.begin(115200);
}

void loop(){
	Serial.println("Forward!");
	mA.right();
	mB.right();
	delay(1000);
	Serial.println("Stop!");
	mA.stop();
	mB.stop();
	delay(1000);

	Serial.println("Backward!");
	mA.left();
	mB.left();
	delay(1000);
	Serial.println("Stop!");
	mA.stop();
	mB.stop();
	delay(1000);

	Serial.println("Right?");
	mA.right();
	mB.left();
	delay(1000);
	Serial.println("Stop!");
	mA.stop();
	mB.stop();
	delay(1000);

	Serial.println("Left?");
	mA.left();
	mB.right();
	delay(1000);
	Serial.println("Stop!");
	mA.stop();
	mB.stop();
	delay(2000);
}