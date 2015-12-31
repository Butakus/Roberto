/* Library to control a robot's base using the Motor library
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	04/11/2015
*/

#include "RobotBase.h"
#include <Motor.h>


RobotBase::RobotBase(Motor *m1, Motor *m2){
	_left_motor = m1;
	_right_motor = m2;
	_left_speed = 0;
	_right_speed = 0;
	_left_motor->set_speed(_left_speed);
	_left_motor->stop();
	_right_motor->set_speed(_right_speed);
	_right_motor->stop();	
}

RobotBase::~RobotBase(){}

void RobotBase::set_left_speed(uint8_t speed){
	_left_motor->set_speed(speed);
	_left_speed = _left_motor->get_speed();
}

void RobotBase::set_right_speed(uint8_t speed){
	_right_motor->set_speed(speed);
	_right_speed = _right_motor->get_speed();
}

void RobotBase::set_speed(uint8_t speed){
	set_left_speed(speed);
	set_right_speed(speed);
}

void RobotBase::forward(){
	if (_left_speed > _right_speed){
		_right_speed = _left_speed;
	}
	else if (_right_speed > _left_speed){
		_left_speed = _right_speed;
	}
	_left_motor->right(_left_speed);
	_right_motor->right(_right_speed);
}

void RobotBase::forward(uint8_t speed){
	_right_speed = speed;	
	_left_speed = speed;
	forward();
}

void RobotBase::backward(){
	if (_left_speed > _right_speed){
		_right_speed = _left_speed;
	}
	else if (_right_speed > _left_speed){
		_left_speed = _right_speed;
	}
	_left_motor->left(_left_speed);
	_right_motor->left(_right_speed);
}

void RobotBase::backward(uint8_t speed){
	_right_speed = speed;	
	_left_speed = speed;
	backward();
}

void RobotBase::left(){
	_left_motor->left(_left_speed);
	_right_motor->right(_right_speed);
}

void RobotBase::left(uint8_t speed){
	_left_speed = speed;
	left();
}

void RobotBase::right(){
	_right_motor->left(_right_speed);
	_left_motor->right(_left_speed);
}

void RobotBase::right(uint8_t speed){
	_right_speed = speed;
	right();
}

void RobotBase::stop(){
	_left_motor->stop();
	_right_motor->stop();
}
