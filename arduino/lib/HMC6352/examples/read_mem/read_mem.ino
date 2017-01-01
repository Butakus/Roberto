/* Read the offset values computed after the calibration routine.
*  Those values are stored in the HMC6352 EEPROM.
*/


#include "HMC6352.h"

HMC6352 compass;

uint8_t data[4];
uint16_t x_offset, y_offset;

void setup() {
	Wire.begin();
	pinMode(13,OUTPUT);
	digitalWrite(13,HIGH);
	Serial.begin(9600);
	delay(1000);
	digitalWrite(13,LOW);

	for (int i = 1; i < 5; ++i){
		data[i-1] = compass.read_EEPROM(i);
		Serial.print("Register ");
		Serial.print(i);
		Serial.print(": ");
		Serial.println(data[i-1]);
	}
	x_offset = 255*data[0] + data[1];
	y_offset = 255*data[2] + data[3];
	Serial.print("X Offset: ");
	Serial.println(x_offset);
	Serial.print("Y Offset: ");
	Serial.println(y_offset);
}

void loop() {


}
