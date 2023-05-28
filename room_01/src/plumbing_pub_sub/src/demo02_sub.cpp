#include "ros/ros.h"
#include "std_msgs/String.h"  //文本类型
#include <sstream>  //拼接
/*
   订阅方实现：
      1.包含头文件；
          ROS中的文本类型 ---> std_msgs/String.h
      2.初始化ROS节点；
      3.创建节点句柄；
      4.创建订阅者对象；
      5.处理订阅到的数据；
      6.声明一个spin()函数。
*/
    //常数定值  传输的信息：：数据类型：：常量指针的引用           
void doMsg(const std_msgs::String::ConstPtr &msg){
    //通过msg获取并操作订阅到的数据
    ROS_INFO("DYZ订阅的数据:%s",msg->data.c_str());  //智能指针

}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");  //中文
    //2.初始化ROS节点；
    ros::init(argc,argv,"DYZ");

    //3.创建节点句柄；
    ros::NodeHandle nh;  //建立联系

    //4.创建发布者对象；              //这里不需要添加范型        
    ros::Subscriber sub = nh.subscribe("money",10,doMsg);  //需要回调函数处理订阅到的信息

    //5.处理订阅到的数据；就算回调函数    调用的时机是外部控制的就算回调函数，订阅到一条message就调用一次

   
        //6.声明一个spin()函数。
        ros::spin();   //回调处理，多次使用回调函数

    return 0;
}