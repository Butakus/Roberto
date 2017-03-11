# Teleoperation Module for Roberto
This is the Arduino code of the application that controls the robot and a robotic arm with the commands received from the Serial port.

The Raspberry Pi part can be found in (https://github.com/Butakus/RobertoTeleop)


## Commands
At this moment the commands available (received from the Serial port) are:

| HEX | DEC | Command |
|-----|-----|:---------|
|0x00 | 0 | stop() |
|0x03 | 3 | forward(speed) |
|0x0C | 12 | backward(speed) |
|0x0F | 15 | left(speed) |
|0x30 | 48 | right(speed) |
|0x33 | 51 | arm_left() |
|0x3C | 60 | arm_right() |
|0x3F | 63 | arm_up() |
|0xC0 | 192 | arm_down() |
|0xC3 | 195 | arm_h_pos(pos) |
|0xCC | 204 | arm_v_pos(pos) |
|0xCF | 207 | wrist_left() |
|0xF0 | 240 | wrist_right() |
|0xF3 | 243 | wrist_pos(pos) |
|0xFC | 252 | open_grasp() |
|0xFF | 255 | close_grasp() |
