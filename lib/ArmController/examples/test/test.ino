/* Library to control a servo-based robotic arm with 3 freedom degrees + grasp
*  in an intuitive way.
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	12/11/2015
*/

#include <ArmController.h>

#define ARM_H_PIN 8
#define ARM_V_PIN 9
#define WRIST_PIN 10
#define GRASP_PIN 11

ArmController arm(ARM_H_PIN, ARM_V_PIN, WRIST_PIN, GRASP_PIN);

int pot_pin = 0;
int val = 0;

void setup(){
	Serial.begin(9600);	
}

void loop(){
	val = map(analogRead(pot_pin), 0, 1024, 0, 180);
	Serial.print("Val: ");
	Serial.println(val);
	//arm.set_arm_h_pos(val);
	delay(100);
}