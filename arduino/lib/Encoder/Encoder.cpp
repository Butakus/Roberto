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

#include "Encoder.h"



const int8_t SingleEncoder::encoder_lookup_[] = {0,0,0,-1,0,0,1,0,0,1,0,0,-1,0,0,0};
