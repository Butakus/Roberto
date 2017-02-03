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
    _last_ack = ACK_UNSET;
    _retries = 0;
}

ArdPiComm::~ArdPiComm(){}


/* Initialize the serial object. serial.begin() must be called before this */
void ArdPiComm::begin(Stream *port)
{
    _serial = port;
}


/* Read all bytes in the serial buffer and check if a new frame is available.
*  Return 1 if a new packet is available, else 0
*/
uint8_t ArdPiComm::read()
{
    // Read all bytes in the serial buffer
    uint8_t new_packet = 0;
    while (_serial->available())
    {
        _in_buffer[_buffer_index++] = _serial->read();
        if (_in_buffer[_buffer_index - 1] == START_FLAG && (_buffer_index - 3) > 0)
        {
            // There is a complete frame in the buffer. Process it.
            new_packet = process_frame();
            // After processing the frame, clear the index to reuse the buffer
            _buffer_index = 0;
        }
    }

    return new_packet;
}


/* Send a packet given the command and the payload */
TX_Error ArdPiComm::send(uint8_t command, uint8_t payload_size, uint8_t payload[])
{
    
    _sent_seq = (_sent_seq + 1) % 256;

    // Reset last ack
    _last_ack = ACK_UNSET;

    // Compute the checksum of the data to send
    uint16_t computed_checksum = checksum(_sent_seq, command, payload_size, payload);


    // Send all bytes, escaping if necessary
    // Start flag
    _serial->write(START_FLAG);
    
    // Sequence number
    if (_sent_seq == START_FLAG || _sent_seq == ESCAPE_FLAG)
    {
        _serial->write(ESCAPE_FLAG);
        _serial->write(_sent_seq ^ (1 << 5));
    }
    else
    {
        _serial->write(_sent_seq);
    }
    
    // Command
    if (command == START_FLAG || command == ESCAPE_FLAG)
    {
        _serial->write(ESCAPE_FLAG);
        _serial->write(command ^ (1 << 5));
    }
    else
    {
        _serial->write(command);
    }
    
    // Payload size
    if (payload_size == START_FLAG || payload_size == ESCAPE_FLAG)
    {
        _serial->write(ESCAPE_FLAG);
        _serial->write(payload_size ^ (1 << 5));
    }
    else
    {
        _serial->write(payload_size);
    }

    // Payload
    for (int i = 0; i < payload_size; ++i)
    {
        if (payload[i] == START_FLAG || payload[i] == ESCAPE_FLAG)
        {
            _serial->write(ESCAPE_FLAG);
            _serial->write(payload[i] ^ (1 << 5));
        }
        else
        {
            _serial->write(payload[i]);
        }
    }

    // Checksum
    uint8_t checksum_msb = (computed_checksum & 0xFF00) >> 8;
    uint8_t checksum_lsb = computed_checksum & 0x00FF;

    if (checksum_msb == START_FLAG || checksum_msb == ESCAPE_FLAG)
    {
        _serial->write(ESCAPE_FLAG);
        _serial->write(checksum_msb ^ (1 << 5));
    }
    else
    {
        _serial->write(checksum_msb);
    }
    if (checksum_lsb == START_FLAG || checksum_lsb == ESCAPE_FLAG)
    {
        _serial->write(ESCAPE_FLAG);
        _serial->write(checksum_lsb ^ (1 << 5));
    }
    else
    {
        _serial->write(checksum_lsb);
    }

    // End flag
    _serial->write(START_FLAG);


    // Wait for the ACK
    TX_Error error = wait_ack();
    if (error == NO_ERROR)
    {
        // Get ACK
        if (_last_ack == ACK_RETRY)
        {
            // Retry
            if (++_retries >= MAX_RETRIES)
            {
                error = ACK_ERROR;
            }
            else
            {
                error = send(command, payload_size, payload);
            }
        }
        else
        {
            // ACK OK
            error = NO_ERROR;
        }
    }
    return error;
}


/* Send a packet with just a command */
TX_Error ArdPiComm::send(uint8_t command)
{
    return send(command, 0, NULL);
}


uint8_t ArdPiComm::get_command()
{
    return _command;
}


uint8_t ArdPiComm::get_payload(uint8_t payload[])
{
	for (int i = 0; i < _payload_size; ++i)
	{
	    payload[i] = _payload[i];
	}
    return _payload_size;
}


/* Get the frame sequence from the buffer, extract the frame data and process it */
uint8_t ArdPiComm::process_frame()
{
    uint8_t new_packet = 0;
    // Array to store the buffer data after removing escape flags
    uint8_t escaped_data[_buffer_index];
    uint8_t total_size = 0;
    // Unescape the data
    for (int i = 0; i < _buffer_index; ++i)
    {
        uint8_t b = _in_buffer[i];
        if (b == ESCAPE_FLAG)
        {
            b = _in_buffer[++i] ^ (1 << 5);
        }
        escaped_data[total_size++] = b;
    }

    if (escaped_data[COMMAND] == ACK_COMMAND)
    {
        // Received an ACK frame. Set the ack value.
        if (escaped_data[SEQ_NUMBER] == _sent_seq)
        {
            _last_ack = ACK_RETRY;
        }
        else
        {
            _last_ack = ACK_OK;
        }
    }
    else
    {
        // Received a packet frame. Update the command and payload fields
        uint8_t retry = 0;

        // Copy frame data
        _command = escaped_data[COMMAND];
        _payload_size = escaped_data[PAYLOAD_SIZE];
        for (int i = 0; i < _payload_size; ++i)
        {
            _payload[i] = escaped_data[i+4];
        }

        // Check size and checksum
        if (_payload_size != total_size - 7) retry = 1;
        uint16_t received_checksum = (escaped_data[total_size - 3] << 8) | escaped_data[total_size - 2];
        uint16_t computed_checksum = checksum(escaped_data[SEQ_NUMBER], _command, _payload_size, _payload);
        if (received_checksum != computed_checksum) retry = 1;

        // Send ACK
        if (retry)
        {
            send_ack(escaped_data[SEQ_NUMBER]);
        }
        else
        {
            // Packet RX ok
            new_packet = 1;
            send_ack((escaped_data[SEQ_NUMBER] + 1) % 256);
        }
    }
    return new_packet;
}


/* Wait and read until a new ACK arrives 
*  Returns TIMEOUT_ERROR if TIMEOUT is exceded, NO_ERROR otherwise.
*/
TX_Error ArdPiComm::wait_ack()
{
    unsigned long start_time = millis();
    TX_Error error = NO_ERROR;
    while (_last_ack == ACK_UNSET)
    {
        if ((millis() - start_time) > TIMEOUT)
        {
            error = TIMEOUT_ERROR;
            break;
        }
        read();
    }
    return error;
}


/* Send an ACK response */
void ArdPiComm::send_ack(uint8_t seq_number)
{

    // Send all bytes, escaping if necessary
    // Start flag
    _serial->write(START_FLAG);
    
    // Sequence number
    if (seq_number == START_FLAG || seq_number == ESCAPE_FLAG)
    {
        _serial->write(ESCAPE_FLAG);
        _serial->write(seq_number ^ (1 << 5));
    }
    else
    {
        _serial->write(seq_number);
    }
    
    // Command
    _serial->write(ACK_COMMAND);

    // End flag
    _serial->write(START_FLAG);
}


/* Compute the 16bit Fletcher's checksum of the data */
uint16_t ArdPiComm::checksum(uint8_t seq_number, uint8_t command, uint8_t payload_size, uint8_t payload[])
{
    uint16_t lsb = 0;
    uint16_t  msb = 0;

    lsb += seq_number;
    msb += lsb;
    lsb += command;
    msb += lsb;
    lsb += payload_size;
    msb += lsb;

    for (int i = 0; i < payload_size; ++i)
    {
        lsb += payload[i];
        msb += lsb;
        if (i % 16 == 0)
        {
            // Do a reduction each 16 bytes;
            lsb = (lsb & 0xFF) + (lsb >> 8);
            msb = (msb & 0xFF) + (msb >> 8);
        }
        
    }
    // Last double reduction to add the carry;

    lsb = (lsb & 0xFF) + (lsb >> 8);
    lsb = (lsb & 0xFF) + (lsb >> 8);
    msb = (msb & 0xFF) + (msb >> 8);
    msb = (msb & 0xFF) + (msb >> 8);

    return (msb << 8) | lsb;
}
