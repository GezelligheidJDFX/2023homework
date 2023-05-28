#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"

void back(const plumbing_pub_sub::Person::ConstPtr& person)  //括号里要声明订阅到的数据,文件名里的person数据里的常量指针
{
    ROS_INFO("订阅人的信息：%s,%d,%.2f",person->name.c_str(),person->age,person->height);

}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ROS_INFO("订阅方实现");

    ros::init(argc,argv,"jiazhang");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("liaotian",10,back);

    ros::spin();

    return 0;
}