/* Library to control a robot's base using the Motor library
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	04/11/2015
*/

#ifndef RobotBase_h
#define RobotBase_h

#include <Arduino.h>
#include <Motor.h>

class RobotBase
{
public:
	RobotBase(Motor *, Motor *);
	~RobotBase();
	
	void forward();
	void forward(uint8_t);
	void backward();
	void backward(uint8_t);
	void left();
	void left(uint8_t);
	void right();
	void right(uint8_t);
	void stop();
	void set_speed(uint8_t);
	void set_left_speed(uint8_t);
	void set_right_speed(uint8_t);
	
private:
	Motor *_left_motor;
	Motor *_right_motor;
	uint8_t _left_speed;
	uint8_t _right_speed;
};

#endif