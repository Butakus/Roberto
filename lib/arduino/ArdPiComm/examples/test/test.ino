/* Library to implement the communication protocol between the Arduino and
*  the Raspberry Pi in Roberto over a Serial port.
*  
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	11/11/2015
*/

#include <ArdPiComm.h>

ArdPiComm comms;
uint8_t command, argument, error;

void setup(){
	Serial.begin(9600);
	comms.begin(&Serial);

	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	delay(1000);
	digitalWrite(13, LOW);
}

void loop(){
	error = comms.read(&command, &argument);
	if (error == NO_ERROR){
		if (command == 0x00){
			digitalWrite(13,LOW);
		}
		else if (command == 0x03){
			digitalWrite(13,HIGH);
		}
		delay(2000);
	}
	else{
		digitalWrite(13,HIGH);
		delay(5000);
		digitalWrite(13, LOW);
	}
}
