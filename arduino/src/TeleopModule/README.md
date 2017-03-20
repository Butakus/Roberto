# Teleoperation Module for Roberto
This is the Arduino code of the application that controls the robot with the commands received from the Serial port.


## Commands
At this moment the commands available (received from the Serial port) are:

| HEX | DEC | Command |
|-----|-----|:---------|
|0x00 | 0 | stop() |
|0x03 | 3 | forward(speed) |
|0x0C | 12 | backward(speed) |
|0x0F | 15 | left(speed) |
|0x30 | 48 | right(speed) |
