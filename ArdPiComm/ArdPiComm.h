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

#ifndef ArdPiComm_h
#define ArdPiComm_h

#include <Arduino.h>

#define COMM_TIMEOUT 2000
#define ACK_CODE 1
#define RETRY_CODE 0
#define NO_ERROR 0
#define ARG_TIMEOUT_ERROR 1 // Not used (yet)
#define DEAD_TIMEOUT_ERROR 2

class ArdPiComm{

public:
	ArdPiComm();
	~ArdPiComm();
	void begin(Stream *);
	uint8_t read(uint8_t *, uint8_t *);
	uint8_t get_command();
	uint8_t get_arg();
	
private:
	Stream *_serial;
	uint8_t _command;
	uint8_t _argument;
	double _start_time;
	void response(uint8_t);
};

#endif