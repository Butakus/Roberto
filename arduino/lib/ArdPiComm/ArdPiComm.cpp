/* Library to implement the communication protocol between the Arduino and
*  the Raspberry Pi in Roberto over a Serial port.
*  
*  The communication protocol is based on HLDLC with ARQ-StopAndWait error control.
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.2
*  Date:    February 2017
*/

#include "ArdPiComm.h"


ArdPiComm::ArdPiComm()
{
    _command = 0;
    _buffer_index = 0;
    _start_time = 0;
    _payload_size = 0;
    _sent_seq = 0;
    _last_ack = 0;
    _retries = 0;
}

ArdPiComm::~ArdPiComm(){}

void ArdPiComm::begin(Stream *port)
{
    _serial = port;
}

uint8_t ArdPiComm::read()
{
    // TODO
    /*
        Read all bytes in the serial buffer and check if a new frame is available.
        Return 1 if a new frame is available, else 0
    */

    /* OLD read function
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
    */
    return 0;
}

uint8_t ArdPiComm::send(uint8_t command, uint8_t payload_size, uint8_t* payload)
{
    // TODO
    /* Send a packet given the command and the payload */
    return 0;
}


uint8_t ArdPiComm::get_command()
{
    // TODO
    return _command;
}

uint8_t ArdPiComm::get_payload(uint8_t* payload)
{
    // TODO
    payload = _payload;
    return _payload_size;
}


void ArdPiComm::process_frame(uint8_t start, uint8_t end)
{
    // TODO
    /* Get the frame sequence from the buffer, extract the frame data and process it */
}

void ArdPiComm::invert_bit_5(uint8_t* val)
{
    // TODO
    /* Invert the 5th bit */
}

void ArdPiComm::check_flag_conflict(uint8_t val)
{
    // TODO
    /* Check if the byte conflicts with one of the flags */
}

uint8_t ArdPiComm::wait_ack()
{
    // TODO
    /* Wait and read until a new ACK arrives */
    return 0;
}

void ArdPiComm::send_ack(uint8_t seq_number)
{
    // TODO
    /* Send an ACK response */
}

uint16_t ArdPiComm::checksum(uint8_t seq_num, uint8_t command, uint8_t payload_size, uint8_t* payload)
{
    // TODO
    /* Compute the 16bit Fletcher's checksum of the data */
    return 0;
}
