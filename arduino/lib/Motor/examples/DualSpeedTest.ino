/* Program to test the speed of the robot base.
*  The speed of each motor is controlled by one potentiometer.
*  One switch enables the motors, and another switch changes the direction (for/back)
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    21/01/2017
*/

#include <Motor.h>
#include <LCD.h>

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

Motor motor_left(pin_A1,pin_A2,pin_enA);
Motor motor_right(pin_B1,pin_B2,pin_enB);

LCD lcd;

void setup()
{
    lcd.init();
    lcd.brillo(100);

    pinMode(switchEnable, INPUT);
    pinMode(switchDirection, INPUT);

    delay(500);
}

void loop()
{
    // Clear the screen
    lcd.clear();

    // Get speed from analog potentiometers
    speedA = map(analogRead(potA), 0, 1023, 0, 255);
    speedB = map(analogRead(potB), 0, 1023, 0, 255);
    // Set motors speed
    motor_left.set_speed(speedA);
    motor_right.set_speed(speedB);

    // Debug info
    lcd.cursorPos(1,1);
    Serial.print("L: ");
    Serial.print(motor_left.get_speed());
    lcd.cursorPos(2,1);
    Serial.print("R: ");
    Serial.print(motor_right.get_speed());

    // Movement
    if (digitalRead(switchEnable))
    {
        if (digitalRead(switchDirection))
        {
            motor_left.right();
            motor_right.right();
        }
        else
        {
            motor_left.left();
            motor_right.left();
        }
    }
    else
    {
        motor_left.stop();
        motor_right.stop();
    }

    delay(100);
}