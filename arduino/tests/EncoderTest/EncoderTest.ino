#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

// Arduino Mega 2560 interrupt pins
#define PIN_ENCODER_LEFT_0  2
#define PIN_ENCODER_LEFT_1  3
#define PIN_ENCODER_RIGHT_0 18
#define PIN_ENCODER_RIGHT_1 19

Encoder encoder_left(PIN_ENCODER_LEFT_0, PIN_ENCODER_LEFT_1);
Encoder encoder_right(PIN_ENCODER_RIGHT_0, PIN_ENCODER_RIGHT_1);

int32_t left_count = 0;
int32_t right_count = 0;

void setup()
{
    Serial.begin(115200);
    delay(500);
}

void loop()
{
    left_count = encoder_left.read();
    right_count = encoder_right.read();
    Serial.print("L: ");
    Serial.print(left_count);
    Serial.print("\tR: ");
    Serial.println(right_count);

    delay(100);
}
