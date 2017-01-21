/* Library to control a robot's base using the Motor library
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    04/11/2015
*/

#include <Motor.h>
#include <RobotBase.h>

//Arduino pins
#define pin_A1 52
#define pin_A2 53
#define pin_enA 6
#define pin_B1 48
#define pin_B2 49
#define pin_enB 7

Motor mA(pin_A1,pin_A2,pin_enA);
Motor mB(pin_B1,pin_B2,pin_enB);
RobotBase base(&mB, &mA);

void setup(){
    base.set_speed(255);
    base.stop();
}

void loop(){
    base.forward();
    delay(2000);
    base.stop();
    delay(1000);
    base.backward();
    delay(2000);
    base.stop();
    delay(1000);
    base.left();
    delay(2000);
    base.stop();
    delay(1000);
    base.right();
    delay(2000);
    base.stop();
    delay(5000);
}