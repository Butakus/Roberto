""" [DEPRECATED] Module to teleoperate roberto using raw sockets.
    This file is the main script thatconnects the master with the Arduino
"""

from time import sleep
from master_comm import MasterComm
# Import modules from rpi/lib
from driver_comm import ArdPiComm

# Roberto modules
# Include roberto library dir to python path
import sys, os.path, inspect
current_path = os.path.realpath(os.path.dirname((inspect.getfile(inspect.currentframe()))))
base_path = ""
while base_path != "rpi":
    current_path, base_path = os.path.split(current_path)
sys.path.insert(1, os.path.realpath(os.path.join(current_path, base_path, "lib")))

""" Commands received from master:
    stop
    forward
    backward
    left
    right
    arm_left
    arm_right
    arm_v_pos
    wrist_pos
    open_grasp
    close_grasp
"""

""" Command code list. 
    Keys are received from the master (as strings)
    We must send the corresponding code value to the driver.
"""
DRIVER_COMMANDS = {
    "stop" :        0x00,
    "forward" :     0x03,
    "backward" :    0x0C,
    "left" :        0x0F,
    "right" :       0x30,
    "arm_left" :    0x33,
    "arm_right" :   0x3C,
    "arm_up" :      0x3F,
    "arm_down" :    0xC0,
    "arm_h_pos" :   0xC3,
    "arm_v_pos" :   0xCC,
    "wrist_left" :  0xFF,
    "wrist_right" : 0xF0,
    "wrist_pos" :   0xF3,
    "open_grasp" :  0xFC,
    "close_grasp" : 0xFF
}

driver = None


def command_callback(command, argument):
    # Try to parse the argument into an integer
    try:
        argument = int(argument)
    except ValueError, ve:
        print 'Argument error, not integer'
    else:
        print 'Received command: {}({})'.format(command, argument)
        print 'Sending command: {}({})'.format(DRIVER_COMMANDS[command], argument)
        driver.send(DRIVER_COMMANDS[command], [argument])


def rx_callback(command, payload):
    # Ignore everything comming from the arduino
    pass


if __name__ == '__main__':
    driver = ArdPiComm(rx_callback)
    master = MasterComm(command_callback)
    master.start()
    print "Enter 'q' to exit"
    while True:
        stop = raw_input()
        if stop == 'q':
            break
    driver.stop()
    master.stop()
