/* Library to control CC motors with an H-bridge
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno for @ProyectoSirena
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	21/01/2015
*/

/* Functions:
*	Motor(int,int,int) //Constructor. Creates the object given the pins where the motor is connected
*	set_speed(int) // Changes the motor's speed in the range [0-255]
*	get_speed() // Returns the Motor's speed
*	right() // Turns in one direction
*	left() // Turns in the other direction
*	right(int) // Sets the speed and turn
*	left(int) // Sets the speed and turn
*	stop() // Stops the motor setting both pins to 0
*	brake() // Blocks the motor setting both pins to 1. Not recommended, can damage the motor
*	set_pin1(int) // Changes the first pin
*	set_pin2(int) // Changes the second pin
*	set_en(int) // Changes the enable pin
*/

#include "Motor.h"


Motor::Motor(uint8_t pin1, uint8_t pin2, uint8_t enable){
	setup(pin1, pin2, enable);
	_speed = 0;
}

Motor::Motor(){
	_speed = 0;
}

Motor::~Motor(){}

void Motor::setup(uint8_t pin1, uint8_t pin2, uint8_t enable){
	_pin1 = pin1;
	_pin2 = pin2;
	_en = enable;
	pinMode(_pin1,OUTPUT);
	pinMode(_pin2,OUTPUT);
	pinMode(_en,OUTPUT);
}

void Motor::set_speed(uint8_t speed){
	_speed = constrain(speed, 0, 255);
	analogWrite(_en, _speed);
}


uint8_t Motor::get_speed(){
	return _speed;
}

void Motor::right(){
	digitalWrite(_pin1, HIGH);
	digitalWrite(_pin2, LOW);
	analogWrite(_en, map(_speed,0,100,0,255));
}

void Motor::left(){
	digitalWrite(_pin1, LOW);
	digitalWrite(_pin2, HIGH);
	analogWrite(_en, map(_speed,0,100,0,255));	
}

void Motor::right(uint8_t speed){
		set_speed(speed);
		right();
}

void Motor::left(uint8_t speed){
		set_speed(speed);
		left();
}

void Motor::stop(){
	digitalWrite(_pin1, LOW);
	digitalWrite(_pin2, LOW);
}

void Motor::brake(){
	digitalWrite(_pin1, HIGH);
	digitalWrite(_pin2, HIGH);
}

void Motor::set_pin1(uint8_t pin1){
	_pin1 = pin1;
	pinMode(_pin1, OUTPUT);
}

void Motor::set_pin2(uint8_t pin2){
	_pin2 = pin2;
	pinMode(_pin2, OUTPUT);
}

void Motor::set_en(uint8_t enable){
	_en = enable;
	pinMode(_en, OUTPUT);
}
