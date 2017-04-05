/* Module to parse and serialize the data from/into the bytes received/to send
*
*  TODO: Docs  
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.2
*  Date:    April 2017
*/

#ifndef ArdPiParser_h
#define ArdPiParser_h

#include <Arduino.h>

char parse_char(uint8_t* data);
String parse_string(uint8_t* data, uint8_t length);

int8_t parse_int8(uint8_t* data);
uint16_t parse_uint16(uint8_t* data);
int16_t parse_int16(uint8_t* data);
uint32_t parse_uint32(uint8_t* data);
int32_t parse_int32(uint8_t* data);

float parse_float(uint8_t* data);


void serialize_char(char& data, uint8_t* buffer);
void serialize_string(String& data, uint8_t* buffer);

void serialize_int8(int8_t& data, uint8_t* buffer);
void serialize_uint16(uint16_t& data, uint8_t* buffer);
void serialize_int16(int16_t& data, uint8_t* buffer);
void serialize_uint32(uint32_t& data, uint8_t* buffer);
void serialize_int32(int32_t& data, uint8_t* buffer);

void serialize_float(float& data, uint8_t* buffer);

#endif