#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
/* 
    实现：发布速度消息
        话题：/turtle1/cmd_vel
        消息：geometry_msgs/Twist

    1.包含头文件
    2.初始化 ROS 节点
    3.创建节点句柄
    4.创建发布对象
    5.发布逻辑
    6.spinOnce()
*/

int main(int argc ,char *argv[])
{
    ros::init(argc,argv,"my_control");

    ros::NodeHandle l;

    ros::Publisher zwt = l.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);

    ros::Rate rate(10);

    geometry_msgs::Twist control_xwg;

    control_xwg.linear.x = 3.0;
    control_xwg.linear.y = 0.0;
    control_xwg.linear.z = 0.0;

    control_xwg.angular.x = 0.0;
    control_xwg.angular.y = 0.0;
    control_xwg.angular.z = 1.0;

    while(ros::ok())
    {
        zwt.publish(control_xwg);

        rate.sleep();

        ros::spinOnce();
    }

    return 0;
}