/* Main program to run in the arduino.
*  Receive the commands from the Raspberry Pi through ArdPiComm library
*  and control the robot and its arm with RobotBase and ArmController libraries.
* 
*  Commands implemented in commands.ino file.
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.1
*  Date:    12/11/2015
*/

#include <Motor.h>
#include <RobotBase.h>
#include <ArdPiComm.h>


// Arduino MEGA pins
// Motors pins
#define MotorA1_PIN 52
#define MotorA2_PIN 53
#define EnableA_PIN 6
#define MotorB1_PIN 48
#define MotorB2_PIN 49
#define EnableB_PIN 7

/*
// Arduino UNO pins
// Motors pins
#define MotorA1_PIN 2
#define MotorA2_PIN 4
#define EnableA_PIN 5
#define MotorB1_PIN 7
#define MotorB2_PIN 8
#define EnableB_PIN 6

*/


Motor mRight(MotorA1_PIN, MotorA2_PIN, EnableA_PIN);
Motor mLeft(MotorB1_PIN, MotorB2_PIN, EnableB_PIN);
RobotBase base(&mLeft, &mRight);

ArdPiComm comms;

uint8_t payload[100];

void setup(){
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
  
    Serial3.begin(BAUDRATE);
    comms.begin(&Serial3);

    base.stop();
    base.set_speed(255);

    delay(5000);
    digitalWrite(13, LOW);
}

void loop(){
    // digitalWrite(13, HIGH);
    // delay(500);
    // digitalWrite(13, LOW);
    // delay(500);

    if (comms.read())
    {
        uint8_t command = comms.get_command();
        uint8_t payload_size = comms.get_payload(payload);
        if (payload_size > 0)
        {
            // Payload contains always 1 argument byte
            uint8_t speed = payload[0];
            switch (command){
                case 0x03:  forward(speed);      break;
                case 0x0C:  backward(speed);     break;
                case 0x0F:  left(speed);         break;
                case 0x30:  right(speed);        break;
                default:    stop();              break;
            }
        }
        else
        {
            stop();
        }
    }
    delay(20);
}
