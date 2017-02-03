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

#ifndef ArdPiComm_h
#define ArdPiComm_h

#include <Arduino.h>

#define BAUDRATE 57600
#define TIMEOUT 3000
#define MAX_RETRIES 3

#define START_FLAG 0x7E
#define ESCAPE_FLAG 0x7D
#define ACK_COMMAND 0x01

typedef enum tx_error
{
    NO_ERROR = 0,
    TIMEOUT_ERROR,
    ACK_ERROR
} TX_Error;

typedef enum ack_value
{
    ACK_UNSET = 0,
    ACK_OK,
    ACK_RETRY
} ACK_Value;

enum frame_index
{
    FLAG = 0,
    SEQ_NUMBER = 1,
    COMMAND = 2,
    PAYLOAD_SIZE = 3
};

class ArdPiComm{

public:
    ArdPiComm();
    ~ArdPiComm();

    /* Initialize the serial object. serial.begin() must be called before this */
    void begin(Stream* serial);

    /* Read all bytes in the serial buffer and check if a new frame is available.
    *  Return 1 if a new packet is available, else 0
    */
    uint8_t read();

    /* Send a packet given the command and the payload */
    TX_Error send(uint8_t command, uint8_t payload_size, uint8_t payload[]);
    /* Send a packet given with just a command */
    TX_Error send(uint8_t command);

    /* Get the data from the last packet received */
    uint8_t get_command();
    uint8_t get_payload(uint8_t payload[]);
    
private:
    Stream *_serial;
    uint8_t _in_buffer[64];
    uint8_t _buffer_index;

    uint8_t _command;
    uint8_t _payload[64];
    uint8_t _payload_size;
    uint8_t _sent_seq;
    ACK_Value _last_ack;
    uint8_t _retries;
    uint32_t _start_time;

    /* Get the frame sequence from the buffer, extract the frame data and process it */
    uint8_t process_frame();

    /* Wait and read until a new ACK arrives 
    *  Returns TIMEOUT_ERROR if TIMEOUT is exceded, NO_ERROR otherwise.
    */
    TX_Error wait_ack();

    /* Send an ACK response */
    void send_ack(uint8_t seq_number);

    /* Compute the 16bit Fletcher's checksum of the data */
    uint16_t checksum(uint8_t seq_number, uint8_t command, uint8_t payload_size, uint8_t payload[]);
};

#endif