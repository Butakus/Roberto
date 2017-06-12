#!/usr/bin/python2

from roberto_driver.driver_comm import *

import rospy
from geometry_msgs.msg import Twist

# ArdPiComm object
comms = None

""" Command code list.
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


def comms_callback(command, payload):
    """ Callback to process the data received from the arduino """
    print "\t\tCommand received: {}".format(command)
    print "\t\tPayload:"
    print "\t\t{}".format(payload)


def velocity_callback(twist_msg):
    print "New msg: {}".format(twist_msg.angular.z)
    """ Receive velocity msgs and send the proper commands to the arduino """
    if twist_msg.linear.x > 0.01:
        # Forward
        speed = int(255 * min(twist_msg.linear.x, 1.0))
        rospy.logdebug("[ROBERTO_DRIVER] Moving forward at speed %f", speed)
        comms.send(DRIVER_COMMANDS["forward"], [speed])
    elif twist_msg.linear.x < - 0.01:
        # Backward
        speed = int(-255 * max(twist_msg.linear.x, -1.0))
        rospy.logdebug("[ROBERTO_DRIVER] Moving backward at speed %f", speed)
        comms.send(DRIVER_COMMANDS["backward"], [speed])
    elif twist_msg.angular.z < - 0.01:
        # Right
        speed = int(-255 * max(twist_msg.angular.z, -1.0))
        rospy.logdebug("[ROBERTO_DRIVER] Moving right at speed %f", speed)
        comms.send(DRIVER_COMMANDS["right"], [speed])
    elif twist_msg.angular.z > 0.01:
        # Left
        speed = int(255 * min(twist_msg.angular.z, 1.0))
        rospy.logdebug("[ROBERTO_DRIVER] Moving left at speed %f", speed)
        comms.send(DRIVER_COMMANDS["left"], [speed])
    else:
        # Stop
        rospy.logdebug("[ROBERTO_DRIVER] Stopping")
        comms.send(DRIVER_COMMANDS["stop"])


if __name__ == '__main__':
    rospy.init_node('roberto_driver')

    # Comms
    comms = ArdPiComm(comms_callback, port="/dev/serial0")
    comms.start()

    # Subscribers
    rospy.Subscriber("cmd_vel", Twist, velocity_callback, queue_size=1)

    rate = rospy.Rate(100)
    try:
        while not rospy.is_shutdown():
            rate.sleep()
    finally:
        rospy.loginfo("[ROBERTO_DRIVER] Stopping the driver")
        # Stop the robot
        comms.send(DRIVER_COMMANDS["stop"])
        # Close the serial port
        comms.stop()
