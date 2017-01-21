/* Program to test the speed of the robot base.
*  The speed of each motor if controlled by one potentiometer.
*  One switch enables the motors, and another switch chenges the direction (for/back)
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    21/01/2017
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

#define potA 0
#define potB 1
uint8_t speedA = 0;
uint8_t speedB = 0;

#define switchEnable 8
#define switchDirection 9

Motor mA(pin_A1,pin_A2,pin_enA);
Motor mB(pin_B1,pin_B2,pin_enB);
RobotBase base(&mB, &mA);

void setup()
{
    Serial.begin(9600);

    base.set_speed(0);
    base.stop();

    pinMode(switchEnable, INPUT);
    pinMode(switchDirection, INPUT);

    delay(500);
}

void loop()
{
    // Get speed from analog potentiometers
    speedA = map(analogRead(potA), 0, 1023, 0, 255);
    speedB = map(analogRead(potB), 0, 1023, 0, 255);
    // Set motors speed
    base.set_right_speed(speedA);
    base.set_left_speed(speedB);

    // Debug info
    Serial.print(speedA);
    Serial.print("  |  ");
    Serial.println(speedB);

    // Movement
    if (digitalRead(switchEnable))
    {
        if (digitalRead(switchDirection))
            base.forward();
        else 
            base.backward();
    }
    else
    {
        base.stop();
    }

    delay(100);
}