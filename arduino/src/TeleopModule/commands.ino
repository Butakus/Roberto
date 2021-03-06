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

