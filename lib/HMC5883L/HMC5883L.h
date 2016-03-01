/* Arduino library to control the compass HMC5883L.
*
*  Note: Only works woth Arduino IDE v1.0 or greater (arduino.h).
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    24/02/2016
*/


#ifndef HMC5883L_h
#define HMC5883L_h

#include <Arduino.h>
#include "Wire.h"

#define HMC5883L_ADDR 0x3C


class HMC5883L{

public:
    HMC5883L();
    ~HMC5883L();
    void begin();
    float get_heading();
    float get_heading(uint8_t samples);
    uint8_t read_EEPROM(uint8_t mem_address);

    /* TODO
    void start_calibration();
    void stop_calibration();
    void calibrate(uint8_t seconds);
    */
    
private:
    uint8_t address_;
    
    int16_t mag_x_;
    int16_t mag_y_;
    int16_t mag_z_;
    float heading_;

};

#endif