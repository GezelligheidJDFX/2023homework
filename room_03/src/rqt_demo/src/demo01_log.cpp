#include "ros/ros.h"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"log_demo");
    ros::NodeHandle nh;

    ros::Rate r(0.3);
    while(ros::ok())
    {
        ROS_DEBUG("Debug message ohshit");
        ROS_INFO("Info message interesting");
        ROS_WARN("Warn message ohno");
        ROS_ERROR("Error message patience is a key in your life");
        ROS_FATAL("Fatal message surprising");
        r.sleep();
    }
    
    return 0;
}
