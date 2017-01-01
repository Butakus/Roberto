/* Library to implement the communication protocol between the Arduino and
*  the Raspberry Pi in Roberto over a Serial port.
*  
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:	Francisco Miguel Moreno
*  Email:	butakus@gmail.com
*  Version:	0.1
*  Date:	11/11/2015
*/

#include "ArdPiComm.h"


ArdPiComm::ArdPiComm(){
	_command = 0;
	_argument = 0;
	_start_time = 0;
}

ArdPiComm::~ArdPiComm(){}

void ArdPiComm::begin(Stream *port){
	_serial = port;
}

uint8_t ArdPiComm::read(uint8_t *command, uint8_t *argument){
	_command = 0;
	_argument = 0;
	uint8_t error = NO_ERROR;
	_start_time = millis();

	// Block until first byte arrives or we reach a dead timeout
	while ( !_serial->available() && (millis() - _start_time) < 3*COMM_TIMEOUT){
		delay(10);
	}
	
	if (!_serial->available()){
		error = DEAD_TIMEOUT_ERROR;
	}
	else{
		_start_time = millis();
		_command = _serial->read();

		// Block until second byte arrives or the time elapsed pass the timeout
		while ( !_serial->available() && (millis() - _start_time) < COMM_TIMEOUT){
			delay(10);
		}

		if (_serial->available()){
			_argument = _serial->read();
			response(ACK_CODE);
		}
		else{
			// Argument timeout. Retry
			response(RETRY_CODE);
			error = read(command, argument);
		}
	}
	*command = _command;
	*argument = _argument;
	return error;
}

void ArdPiComm::response(uint8_t code){
	if (code == ACK_CODE || code == RETRY_CODE){
		_serial->write(code);
	}
}

uint8_t ArdPiComm::get_command(){
	return _command;
}

uint8_t ArdPiComm::get_arg(){
	return _argument;
}