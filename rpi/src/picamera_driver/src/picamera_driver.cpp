#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "picamera_driver");
    ros::NodeHandle nh, priv_nh("~");
    image_transport::ImageTransport it(nh);

    int width, height;
    priv_nh.param("width", width, 640);
    priv_nh.param("height", height, 480);

    image_transport::Publisher image_pub = it.advertise("picamera/image", 2);
    
    // Camera setup
    raspicam::RaspiCam_Cv camera;
    camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    camera.set(CV_CAP_PROP_FRAME_WIDTH, width);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, height);
    if (!camera.open())
    {
        ROS_ERROR("Could not open pi camera");
        return 1;
    }

    cv::Mat frame;

    ros::Rate rate(10.0);
    while (ros::ok())
    {
        // Get the current frame
        camera.grab();
        camera.retrieve(frame);

        cv_bridge::CvImage image;
        image.header.stamp = ros::Time::now();
        image.encoding = sensor_msgs::image_encodings::BGR8;
        image.image = frame;
        image_pub.publish(image.toImageMsg());

        rate.sleep();
    }
    camera.release();

    return 0;
}