/* Library to implement the communication protocol between the Arduino and
*  the Raspberry Pi in Roberto over a Serial port.
*  
*  The communication protocol is based on HLDLC with ARQ-StopAndWait error control.
*
*  Note: Works only on version 1.0 and above of Arduino IDE. (only arduino.h)
*
*  Author:  Francisco Miguel Moreno
*  Email:   butakus@gmail.com
*  Version: 0.2
*  Date:    February 2017
*/

#include <ArdPiComm.h>

ArdPiComm comms;

void setup(){
    Serial.begin(9600);
    comms.begin(&Serial);

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
}

void loop(){
    comms.read();
    delay(5);
}
