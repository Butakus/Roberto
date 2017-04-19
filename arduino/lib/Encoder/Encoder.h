/* Library to read an encoder using the hardware interruptions
*  The SingleEncoder class is used with 1 interrupt pin and 1 digital pin
*  The DoubleEncoder class is used with 2 interrupt pins
*
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:  Francisco Miguel Moreno for @ProyectoSirena
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    April 2017
*/

#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class SingleEncoder{

public:
    SingleEncoder(uint8_t, uint8_t);
    SingleEncoder();
    ~SingleEncoder();

    void setup(uint8_t, uint8_t);

    volatile unsigned long count;
    

private:
    void ISR_();
    
    const static int8_t encoder_lookup_[];
    volatile uint8_t state_;

};

class DoubleEncoder{

public:
    DoubleEncoder(uint8_t, uint8_t);
    DoubleEncoder();
    ~DoubleEncoder();

    void setup(uint8_t, uint8_t);

    unsigned long count;

private:
    void ISR_();

};

#endif