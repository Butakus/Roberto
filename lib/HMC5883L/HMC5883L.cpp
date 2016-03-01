/* Arduino library to control the compass HMC5883L.
*
*  Note: Only works woth Arduino IDE v1.0 or greater (arduino.h).
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    24/02/2016
*/

#include "HMC5883L.h"


HMC5883L::HMC5883L(){
    address_ = HMC5883L_ADDR >> 1;
    Wire.begin();
}


HMC5883L::~HMC5883L(){}


void HMC5883L::begin(){
    Wire.beginTransmission(address_);
    Wire.write((uint8_t)0x02);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
}

float HMC5883L::get_heading(){

    Wire.beginTransmission(address_);
    Wire.write((uint8_t)0x03);
    Wire.endTransmission();

    // Read the 6 bytes (2 for each axis, MSB first
    Wire.requestFrom(address_, (uint8_t)6);
    uint8_t x_lsb, x_msb, y_lsb, y_msb, z_lsb, z_msb;

    // Block until the data arrives
    while (!Wire.available());
    x_msb = Wire.read();
    x_lsb = Wire.read();
    z_msb = Wire.read();
    z_lsb = Wire.read();
    y_msb = Wire.read();
    y_lsb = Wire.read();

    mag_x_ = (int16_t)(x_lsb | ((int16_t)x_msb << 8));
    mag_y_ = (int16_t)(y_lsb | ((int16_t)y_msb << 8));
    mag_z_ = (int16_t)(z_lsb | ((int16_t)z_msb << 8));

    heading_ = 180.0 * atan2(mag_y_, mag_x_) / M_PI;
    if (heading_ < 0.0) heading_ += 360.0;
    else if (heading_ >= 360.0) heading_ -= 360.0;

    return heading_;
}

// Get the heading applying a median filter to N samples
float HMC5883L::get_heading(uint8_t samples){

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
        delay(5);
    }

    float heading = sorted_data[samples / 2];
    
    /*// If we have enough samples, return the mean of the ones in the middle
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


uint8_t HMC5883L::read_EEPROM(uint8_t mem_address){

    uint8_t data = 0;

    // Only 13 registers (read datasheet). Return 0 for unvalid addresses.
    if (mem_address <= 0){

	    Wire.beginTransmission(address_);
	    Wire.write(mem_address);
	    Wire.endTransmission();

	    Wire.requestFrom(address_, (uint8_t)1);
	    while (!Wire.available());
	    data = Wire.read();
	}

    return data;
}


/* TODO
void HMC5883L::start_calibration(){
}


void HMC5883L::stop_calibration(){
}


void HMC5883L::calibrate(uint8_t seconds){
}

*/
