/*
 * Node is in the incubation state.
 */

#include <ros/ros.h>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    ROS_INFO("OpenCV version: %d.%d.%d", CV_VERSION_MAJOR, CV_VERSION_MINOR, CV_VERSION_REVISION);

    return 0;
}