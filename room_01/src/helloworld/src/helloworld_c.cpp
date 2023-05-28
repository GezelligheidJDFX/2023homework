#include "ros/ros.h"

int main(int argc, char *argv[]){

ros::init(argc,argv,"hello_node");  //后面是节点名称

ROS_INFO("hello world! Hi,JDFX!");   //输出日志

return 0;
} 
