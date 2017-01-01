#include "HMC6352.h"

#define FILTER_SAMPLES 9

HMC6352 compass;
float heading = 0.0;
double t1 = 0.0;
double t2 = 0.0;

void setup() {
	Wire.begin();
	pinMode(13,OUTPUT);
	digitalWrite(13,HIGH);
	Serial.begin(9600);
	delay(1000);
	digitalWrite(13,LOW);
}

void loop() {
	t1 = millis();
	heading = compass.get_heading(FILTER_SAMPLES);
	t2 = millis();
	Serial.print(heading);
	Serial.print(", ");
	Serial.print(t2 - t1);
	Serial.println("ms");
}
