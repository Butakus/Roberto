/* Arduino library to control the compass HMC6352.
*
*  Note: Only works woth Arduino IDE v1.0 or greater (arduino.h).
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    08/02/2016
*/


#ifndef HMC6352_h
#define HMC6352_h

#include <Arduino.h>
#include "Wire.h"

#define HMC6352_ADDR 0x42

// States
enum CompassState {
    OPERATING,
    SLEEPING,
    CALIBRATING
};

class HMC6352{

public:
    HMC6352();
    ~HMC6352();
    float get_heading();
    float get_heading(uint8_t samples);
    void start_calibration();
    void stop_calibration();
    void calibrate(uint8_t seconds);
    uint8_t read_EEPROM(uint8_t mem_address);
    void sleep();
    void wake_up();
    
private:
    uint8_t address_;
    uint8_t heading_data_[2];
    CompassState state_;
};

#endif