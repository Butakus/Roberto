#include "HMC6352.h"

#define CALIBRATION_TIME 20 // Seconds

HMC6352 compass;

void setup() {
	Wire.begin();
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	Serial.begin(9600);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(1000);
	digitalWrite(13, HIGH);

	Serial.println("Starting calibration...");
	compass.start_calibration();
	delay(1000 * CALIBRATION_TIME);
	compass.stop_calibration();
	digitalWrite(13, LOW);
	Serial.println("Calibration finished");
}

void loop() {}
