#include "ros/ros.h"
#include "turtlesim/Pose.h"

void dopose(const turtlesim::Pose::ConstPtr& p)
{
    ROS_INFO("乌龟位姿信息: x = %.2f, y = %.2f, theta = %.2f, lv = %.2f, av = %.2f ",
             p->x,p->y,p->linear_velocity,p->angular_velocity);
}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"sub_pose");

    ros::NodeHandle k;

    ros::Subscriber jdfx = k.subscribe<turtlesim::Pose>("/turtle1/pose",1000,dopose);

    ros::spin(); 

    return 0;
}