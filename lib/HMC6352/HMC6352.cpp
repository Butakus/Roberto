/* Arduino library to control the compass HMC6352.
*
*  Note: Only works woth Arduino IDE v1.0 or greater (arduino.h).
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    08/02/2016
*/

#include "HMC6352.h"


HMC6352::HMC6352(){
    address_ = HMC6352_ADDR >> 1;
    state_ = OPERATING;
    Wire.begin();
}


HMC6352::~HMC6352(){}


float HMC6352::get_heading(){
    // Check if calibration or sleeping states are active
    if (state_ != OPERATING){
        return -1;
    }

    float heading = 0;

    // Send a "A" command to the HMC6352
    // This requests the current heading data
    Wire.beginTransmission(address_);
    Wire.write("A");
    Wire.endTransmission();
    
    // The HMC6352 needs at least a 70us delay after this command.  Using 10ms just makes it safe.
    delay(10);
    
    // Read the 2 heading bytes, MSB first
    Wire.requestFrom(address_, (uint8_t)2);
    // Block until the data arrives
    while (!Wire.available());
    for (int i = 0; i < 2; ++i){ 
        heading_data_[i] = Wire.read();
    }
    
    heading = (float)(heading_data_[0]*256 + heading_data_[1]) / 10.0;
    return heading;
}

// Get the heading applying a median filter to N samples
float HMC6352::get_heading(uint8_t samples){
    // Check if calibration or sleeping states are active
    if (state_ != OPERATING){
        return -1;
    }

    // Better an odd number of samples
    if (samples % 2 == 0) samples++;

    float sorted_data[samples];
    float cur_heading = 0.0;
    int insert_pos = 0;

    // Apply a median filter to the samples
    for (int i = 0; i < samples; ++i){
        insert_pos = 0;
        cur_heading = get_heading();

        // Compute the cur_heading position in the sorted array
        if (cur_heading > sorted_data[0] || i != 0){
            for (int j = 1; j < i; ++j){
                if (cur_heading > sorted_data[j-1] && cur_heading <= sorted_data[j]){
                    insert_pos = j;
                    break;
                }
            }
        }

        // Shift array data and insert new value
        for (int k = i; k > insert_pos; --k){
            sorted_data[k] = sorted_data[k-1];
        }
        sorted_data[insert_pos] = cur_heading;
    }

    float heading = sorted_data[samples / 2];
    
    /*// If we have enough samples, return the mean of the medium ones
    if (samples >= 7){
        for (int i = 0; i < 2; ++i){
            heading += sorted_data[samples/2 + i];
            heading += sorted_data[samples/2 - i];
        }
        heading /= 5;
    }
    */

    return heading;

}


void HMC6352::start_calibration(){
    
    // Check if calibration or sleeping states are active
    if (state_ != OPERATING){
        return;
    }

    Wire.beginTransmission(address_);
    Wire.write("C");
    Wire.endTransmission();
    state_ = CALIBRATING;
}


void HMC6352::stop_calibration(){
    
    // Check if calibration or sleeping states are active
    if (state_ != OPERATING){
        return;
    }

    Wire.beginTransmission(address_);
    Wire.write("E");
    Wire.endTransmission();

    delay(1500); // 14000us needed by the HMC6352 after calibration to update the EEPROM
    state_ = OPERATING;
}


void HMC6352::calibrate(uint8_t seconds){
    
    // Check if calibration or sleeping states are active
    if (state_ != OPERATING){
        return;
    }
    start_calibration();
    delay(1000 * seconds);
    stop_calibration();
}


uint8_t HMC6352::read_EEPROM(uint8_t mem_address){
    
    // Check if calibration or sleeping states are active
    if (state_ != OPERATING){
        return;
    }

    uint8_t data = 0;

    // Only 9 registers (read datasheet). Return the I2C address by default
    if (mem_address > 8) mem_address = 0;

    Wire.beginTransmission(address_);
    Wire.write("r");
    Wire.write(mem_address);
    Wire.endTransmission();

    delay(10);

    Wire.requestFrom(address_, (uint8_t)1);
    while (!Wire.available());
    data = Wire.read();

    return data;
}


void HMC6352::sleep(){
    
    // Check if calibration or sleeping states are active
    if (state_ != OPERATING){
        return;
    }

    Wire.beginTransmission(address_);
    Wire.write("S");
    Wire.endTransmission();

    delay(5);
    state_ = SLEEPING;
}


void HMC6352::wake_up(){
    
    // Check if sleeping state is active
    if (state_ != SLEEPING){
        return;
    }

    Wire.beginTransmission(address_);
    Wire.write("W");
    Wire.endTransmission();

    delay(200);
    state_ = OPERATING;
}