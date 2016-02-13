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

#ifndef ArmController_h
#define ArmController_h

#include <Arduino.h>
#include <Servo.h>

// Limits
#define ARM_H_MIN 0
#define ARM_H_MAX 180
#define ARM_V_MIN 70
#define ARM_V_MAX 180
#define WRIST_MIN 0
#define WRIST_MAX 180
#define GRASP_MIN 50
#define GRASP_MAX 180

// Default step in degrees for relative movement
#define DEFAULT_STEP 5

class ArmController{

public:
	ArmController();
	ArmController(uint8_t arm_h_pin, uint8_t arm_v_pin, uint8_t wrist_pin, uint8_t grasp_pin);
	~ArmController();

	void init(uint8_t arm_h_pin, uint8_t arm_v_pin, uint8_t wrist_pin, uint8_t grasp_pin);

	void set_arm_h_pin(uint8_t pin);
	void set_arm_v_pin(uint8_t pin);
	void set_wrist_pin(uint8_t pin);
	void set_grasp_pin(uint8_t pin);

	uint8_t get_arm_h_pos();
	uint8_t get_arm_v_pos();
	uint8_t get_wrist_pos();
	uint8_t get_grasp_pos();

	void set_arm_h_pos(uint8_t pos);
	void set_arm_v_pos(uint8_t pos);
	void set_arm_pos(uint8_t h_pos, uint8_t v_pos);
	void set_wrist_pos(uint8_t pos);
	void set_grasp_pos(uint8_t pos);

	void move_arm_up();
	void move_arm_up(uint8_t step);
	void move_arm_down();
	void move_arm_down(uint8_t step);
	void move_arm_left();
	void move_arm_left(uint8_t step);
	void move_arm_right();
	void move_arm_right(uint8_t step);

	void move_wrist_left();
	void move_wrist_left(uint8_t step);
	void move_wrist_right();
	void move_wrist_right(uint8_t step);
	
	void open_grasp();
	void open_grasp(uint8_t step);
	void close_grasp();
	void close_grasp(uint8_t step);
	
private:
	Servo _arm_h;
	Servo _arm_v;
	Servo _wrist;
	Servo _grasp;

	uint8_t _arm_h_pos;
	uint8_t _arm_v_pos;
	uint8_t _wrist_pos;
	uint8_t _grasp_pos;

	uint8_t _arm_h_pin;
	uint8_t _arm_v_pin;
	uint8_t _wrist_pin;
	uint8_t _grasp_pin;

	void _update_state();
};

#endif