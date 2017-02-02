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

#define BAUDRATE 9600
#define COMM_TIMEOUT 3000
#define MAX_RETRIES 3

#define START_FLAG 0x7E
#define ESCAPE_FLAG 0x7D
#define ACK_CODE 0x01

#define NO_ERROR 0
#define TIMEOUT_ERROR 1
#define ACK_ERROR 2


class ArdPiComm{

public:
    ArdPiComm();
    ~ArdPiComm();
    void begin(Stream* serial);

    uint8_t read();
    uint8_t send(uint8_t command, uint8_t payload_size, uint8_t* payload);
    uint8_t get_command();
    uint8_t get_payload(uint8_t* payload);
    
private:
    Stream *_serial;
    uint8_t _in_buffer[64];
    uint8_t _buffer_index;

    uint8_t _command;
    uint8_t _payload[64];
    uint8_t _payload_size;
    uint8_t _sent_seq;
    uint8_t _last_ack;
    uint8_t _retries;
    uint32_t _start_time;

    void process_frame(uint8_t start, uint8_t end);
    void invert_bit_5(uint8_t* val);
    void check_flag_conflict(uint8_t val);
    uint8_t wait_ack();
    void send_ack(uint8_t seq_number);
    uint16_t checksum(uint8_t seq_num, uint8_t command, uint8_t payload_size, uint8_t* payload);
};

#endif