#include "ros/ros.h"

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello");
    ROS_INFO("halo,啦啦啦");


    return 0;
}