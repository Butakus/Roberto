#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>

using namespace std;

geometry_msgs::Twist twist_msg;

void joystick_callback(const sensor_msgs::JoyConstPtr joy_msg)
{
    // Reset the msg
    twist_msg = geometry_msgs::Twist();

    // RT -> forward (normalized speed between [0,1])
    double forward = (- joy_msg->axes[5] + 1.0) / 2.0;
    // LT -> backward (normalized speed between [0,1])
    double backward = (- joy_msg->axes[2] + 1.0) / 2.0;
    // Right Joystick -> right/left
    double left = (joy_msg->axes[3] > 0) ? joy_msg->axes[3] : 0.0;
    double right = (joy_msg->axes[3] < 0) ? - joy_msg->axes[3] : 0.0;

    // Get the strongest value to fill the msg
    if (forward > backward && forward > left && forward > right)
    {
        // Limit the range to [0.85,1] to avoid slow speeds
        twist_msg.linear.x = max(forward, 0.85);
    }
    else if (backward > forward && backward > left && backward > right)
    {
        // Limit the range to [0.85,1] to avoid slow speeds
        twist_msg.linear.x = - max(backward, 0.85);
    }
    else if (left > forward && left > backward && left > right)
    {
        // Avoid the joystick center
        if (left > 0.15)
        // Limit the range to [0.85,1] to avoid slow speeds
        twist_msg.angular.z = max(left, 0.85);
    }
    else if (right > forward && right > backward && right > left)
    {
        // Avoid the joystick center
        if (right > 0.15)
        // Limit the range to [0.85,1] to avoid slow speeds
        twist_msg.angular.z = - max(right, 0.85);
    }
}

int main(int argc, char *argv[])
{
    ros::init (argc, argv, "xbox360_teleop");
    ros::NodeHandle node;

    ros::Publisher twist_pub = node.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    ros::Subscriber joystick_sub = node.subscribe("/joy", 2, joystick_callback);

    ros::Rate rate(10.0);
    while(ros::ok())
    {
        ros::spinOnce();
        twist_pub.publish(twist_msg);
        rate.sleep();
    }
    return 0;
}