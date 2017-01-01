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

#include "ArmController.h"

ArmController::ArmController(){
	_arm_h_pos = (ARM_H_MAX - ARM_H_MIN) / 2;
	_arm_v_pos = (ARM_V_MAX - ARM_V_MIN) / 2;
	_wrist_pos = (WRIST_MAX - WRIST_MIN) / 2;
	_grasp_pos = (GRASP_MAX - GRASP_MIN) / 2;
}

ArmController::ArmController(uint8_t arm_h_pin, uint8_t arm_v_pin, uint8_t wrist_pin, uint8_t grasp_pin){
	_arm_h_pos = (ARM_H_MAX - ARM_H_MIN) / 2;
	_arm_v_pos = (ARM_V_MAX - ARM_V_MIN) / 2;
	_wrist_pos = (WRIST_MAX - WRIST_MIN) / 2;
	_grasp_pos = (GRASP_MAX - GRASP_MIN) / 2;

	init(arm_h_pin, arm_v_pin, wrist_pin, grasp_pin);
}

ArmController::~ArmController(){}

void ArmController::init(uint8_t arm_h_pin, uint8_t arm_v_pin, uint8_t wrist_pin, uint8_t grasp_pin){
	set_arm_h_pin(arm_h_pin);
	set_arm_v_pin(arm_v_pin);
	set_wrist_pin(wrist_pin);
	set_grasp_pin(grasp_pin);

	_update_state();
}

void ArmController::set_arm_h_pin(uint8_t pin){
	_arm_h_pin = pin;
	_arm_h.attach(_arm_h_pin);
}

void ArmController::set_arm_v_pin(uint8_t pin){
	_arm_v_pin = pin;
	_arm_v.attach(_arm_v_pin);
}

void ArmController::set_wrist_pin(uint8_t pin){
	_wrist_pin = pin;
	_wrist.attach(_wrist_pin);
}

void ArmController::set_grasp_pin(uint8_t pin){
	_grasp_pin = pin;
	_grasp.attach(_grasp_pin);	
}


uint8_t ArmController::get_arm_h_pos(){
	return _arm_h_pos;
}

uint8_t ArmController::get_arm_v_pos(){
	return _arm_v_pos;
}

uint8_t ArmController::get_wrist_pos(){
	return _wrist_pos;
}

uint8_t ArmController::get_grasp_pos(){
	return _grasp_pos;
}


// Absolute position
void ArmController::set_arm_h_pos(uint8_t pos){
	pos = constrain(pos, ARM_H_MIN, ARM_H_MAX);
	_arm_h_pos = pos;
	_update_state();
}

void ArmController::set_arm_v_pos(uint8_t pos){
	pos = constrain(pos, ARM_V_MIN, ARM_V_MAX);
	_arm_v_pos = pos;
	_update_state();
}

void ArmController::set_wrist_pos(uint8_t pos){
	pos = constrain(pos, WRIST_MIN, WRIST_MAX);
	_wrist_pos = pos;
	_update_state();
}

void ArmController::set_grasp_pos(uint8_t pos){
	pos = constrain(pos, GRASP_MIN, GRASP_MAX);
	_grasp_pos = pos;
	_update_state();
}



// Arm relative position
void ArmController::move_arm_up(){
	move_arm_up(DEFAULT_STEP);
}

void ArmController::move_arm_up(uint8_t step){
	if (_arm_v_pos + step >= ARM_V_MAX) _arm_v_pos = ARM_V_MAX;
	else _arm_v_pos += step;
	_update_state();
}

void ArmController::move_arm_down(){
	move_arm_down(DEFAULT_STEP);
}

void ArmController::move_arm_down(uint8_t step){
	if (_arm_v_pos - step <= ARM_V_MIN) _arm_v_pos = ARM_V_MIN;
	else _arm_v_pos -= step;
	_update_state();
}

void ArmController::move_arm_left(){
	move_arm_left(DEFAULT_STEP);
}

void ArmController::move_arm_left(uint8_t step){
	if (_arm_h_pos + step >= ARM_H_MAX) _arm_h_pos = ARM_H_MAX;
	else _arm_h_pos += step;
	_update_state();
}

void ArmController::move_arm_right(){
	move_arm_right(DEFAULT_STEP);
}

void ArmController::move_arm_right(uint8_t step){
	if (_arm_h_pos - step <= ARM_H_MIN) _arm_h_pos = ARM_H_MIN;
	else _arm_h_pos -= step;
	_update_state();
}


// Wrist relative position
void ArmController::move_wrist_left(){
	move_wrist_left(DEFAULT_STEP);
}

void ArmController::move_wrist_left(uint8_t step){
	if (_wrist_pos + step >= WRIST_MAX) _wrist_pos = WRIST_MAX;
	else _wrist_pos += step;
	_update_state();
}

void ArmController::move_wrist_right(){
	move_wrist_right(DEFAULT_STEP);
}

void ArmController::move_wrist_right(uint8_t step){
	if (_wrist_pos - step <= WRIST_MIN) _wrist_pos = WRIST_MIN;
	else _wrist_pos -= step;
	_update_state();
}

// Grasp relative position
void ArmController::open_grasp(){
	open_grasp(DEFAULT_STEP);
}

void ArmController::open_grasp(uint8_t step){
	if (_grasp_pos + step >= GRASP_MAX) _grasp_pos = GRASP_MAX;
	else _grasp_pos += step;
	_update_state();	
}

void ArmController::close_grasp(){
	close_grasp(DEFAULT_STEP);
}

void ArmController::close_grasp(uint8_t step){
	if (_grasp_pos - step <= GRASP_MIN) _grasp_pos = GRASP_MIN;
	else _grasp_pos -= step;
	_update_state();	
}

void ArmController::_update_state(){
	_arm_h.write(_arm_h_pos);
	_arm_v.write(_arm_v_pos);
	_wrist.write(_wrist_pos);
	_grasp.write(_grasp_pos);
	delay(10);
}
