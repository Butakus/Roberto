#include <ArdPiParser.h>


uint8_t data[100];


void setup()
{
    for (int i = 0; i < 100; i++) data[i] = 55;


    // Parse
    for (int i = 0; i < 100; ++i)
    {
        data[i] = 66;
    }
    
    char c = parse_char(&data[0]);

    data[1] = 226;
    int8_t i8 = parse_int8(&data[1]);

    // 40000
    data[2] = 64;
    data[3] = 156;
    uint16_t ui16 = parse_uint16(&data[2]);
    
    // -300
    data[4] = 212;
    data[5] = 254;    
    int16_t i16 = parse_int16(&data[4]);

    // 1000 000 000
    data[6] = 0;
    data[7] = 202;
    data[8] = 154;
    data[9] = 59;
    uint32_t ui32 = parse_uint32(&data[6]);

    // -1000 000 000
    data[10] = 0;
    data[11] = 54;
    data[12] = 101;
    data[13] = 196;
    int32_t i32 = parse_int32(&data[10]);

    // PI
    data[14] = 219;
    data[15] = 15;
    data[16] = 73;
    data[17] = 64;
    float f = parse_float(&data[14]);


    // Serialize
    uint8_t buffer[100];
    for (int i = 0; i < 100; ++i) buffer[i] = 0;

    serialize_char(c, &buffer[0]);

    serialize_int8(i8, &buffer[1]);
    serialize_uint16(ui16, &buffer[2]);
    serialize_int16(i16, &buffer[4]);
    serialize_uint32(ui32, &buffer[5]);
    serialize_int32(i32, &buffer[9]);

    serialize_float(f, &buffer[13]);
}

void loop(){}