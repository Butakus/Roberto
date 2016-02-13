/* Implementation of the different commands received from the Raspberry Pi.
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	12/11/2015
*/

// Everything implemented in the libraries. Nothing fancy to do here, just linking.

// Movement commands:
void stop(){
	//digitalWrite(13,LOW);
	base.stop();
}

void forward(uint8_t speed){
	//digitalWrite(13,HIGH);
	base.forward(speed);
}

void backward(uint8_t speed){
	base.backward(speed);
}

void left(uint8_t speed){
	base.left(speed);
}

void right(uint8_t speed){
	base.right(speed);
}


// Robotic arm commands:
void arm_left(){
	arm.move_arm_left();
}

void arm_right(){
	arm.move_arm_right();
}

void arm_up(){
	arm.move_arm_up();
}

void arm_down(){
	arm.move_arm_down();
}

void arm_h_pos(uint8_t pos){
	arm.set_arm_h_pos(pos);
}

void arm_v_pos(uint8_t pos){
	arm.set_arm_v_pos(pos);
}

void wrist_left(){
	arm.move_wrist_left();
}

void wrist_right(){
	arm.move_wrist_right();
}

void wrist_pos(uint8_t pos){
	arm.set_wrist_pos(pos);
}

void open_grasp(){
	arm.open_grasp();
}

void close_grasp(){
	arm.close_grasp();
}

