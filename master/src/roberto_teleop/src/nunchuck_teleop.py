#!/usr/bin/python2

""" Teleoperation module that uses the values from the nunchuck accelerometer to compute the speed commands """

from nunchuck_driver.nunchuck_driver import *
from nunchuck_driver.nunchuck_limits import *

import rospy
from geometry_msgs.msg import Twist

def translate(val, src_min, src_max, dst_min, dst_max):
    """ Move a value from the range [src_min,src_max] to [dst_min,dst_max]"""
    src_length = float(src_max - src_min)
    dst_length = float(dst_max - dst_min)
    # [0,1] range
    new_val = float(val - src_min) / src_length
    # [dst_min,dst_max] range
    return dst_min + dst_length*new_val


if __name__ == '__main__':
    rospy.init_node('nunchuck_teleop')

    nunchuck = NunchuckDriver()
    nunchuck.start()
    
    # Velocity publisher
    vel_pub = rospy.Publisher("cmd_vel", Twist, queue_size=1)

    rate = rospy.Rate(10)
    try:
        while not rospy.is_shutdown():
            # Base speed
            twist_msg = Twist()
            # Only send movement messages if Z button is pressed
            if nunchuck.data["buttonZ"] == 1:
                x = nunchuck.data["accelX"]
                y = nunchuck.data["accelY"]
                # Check which movement is stronger (for/back or turn)
                speed = 255.0
                if abs(y) < abs(x): # Y stronger (go for/back)
                    if y < 0 and y > CHUCK_LIM_Y_DOWN_CENTER + 10:
                        if y < (CHUCK_LIM_Y_DOWN - 10):
                            speed = translate(y, CHUCK_LIM_Y_DOWN - 10, CHUCK_LIM_Y_DOWN_CENTER, 255, 200)
                        twist_msg.linear.x = speed / 255.0
                    elif y > 0 and y < CHUCK_LIM_Y_UP_CENTER - 10:
                        if y > (CHUCK_LIM_Y_UP + 10):
                            speed = translate(y, CHUCK_LIM_Y_UP + 10, CHUCK_LIM_Y_UP_CENTER, 255, 200)
                        twist_msg.linear.x = - speed / 255.0
                    else:
                        twist_msg.linear.x = 0.0
                else: # X stronger (turn right/left)
                    if x > 0 and x < CHUCK_LIM_X_LEFT_CENTER - 10:
                        if x > (CHUCK_LIM_X_LEFT + 10):
                            speed = translate(x, CHUCK_LIM_X_LEFT + 10, CHUCK_LIM_X_LEFT_CENTER, 255, 200)
                        twist_msg.angular.z = speed / 255.0
                    elif x < 0 and x > CHUCK_LIM_X_RIGHT_CENTER + 10:
                        if x < (CHUCK_LIM_X_RIGHT - 10):
                            speed = translate(x, CHUCK_LIM_X_RIGHT - 10, CHUCK_LIM_X_RIGHT_CENTER, 255, 200)
                        twist_msg.angular.z = - speed / 255.0
                    else:
                        twist_msg.angular.z = 0.0
            vel_pub.publish(twist_msg)
            rate.sleep()
    except:
        nunchuck.stop()