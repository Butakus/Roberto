/* Library to control CC motors with an H-bridge
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno for @ProyectoSirena
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	21/01/2015
*/

#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor{

public:
	Motor(uint8_t, uint8_t, uint8_t);
	Motor();
	~Motor();

	void setup(uint8_t, uint8_t, uint8_t);
	void set_pin1(uint8_t);
	void set_pin2(uint8_t);
	void set_en(uint8_t);

	void set_speed(uint8_t);
	uint8_t get_speed();

	void right();
	void left();
	void right(uint8_t);
	void left(uint8_t);
	void stop();
	void brake();

private:
	uint8_t _pin1;
	uint8_t _pin2;
	uint8_t _en;
	uint8_t _speed;
};


#endif