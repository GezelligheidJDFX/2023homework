#include "ros/ros.h"
#include "std_msgs/String.h"  //文本类型
#include <sstream>  //拼接
/*
   发布方实现：
      1.包含头文件；
          ROS中的文本类型 ---> std_msgs/String.h
      2.初始化ROS节点；
      3.创建节点句柄；
      4.创建发布者对象；
      5.编写发布者逻辑并发布数据。
*/
int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");  //中文
    //2.初始化ROS节点；
    ros::init(argc,argv,"FBZ");

    //3.创建节点句柄；
    ros::NodeHandle nh;  //建立联系

    //4.创建发布者对象；
    ros::Publisher pub = nh.advertise<std_msgs::String>("money",10);  //话题为money，只缓存10条信息

    //5.编写发布者逻辑并发布数据。     //要求以 10HZ 的频率发布数据，并且文本后添加编号
       //先创建被发布的消息
    std_msgs::String msg;
              //发布频率
                  ros::Rate rate(10);
              //设置编号
                  int count = 0;
       //再编写循环，循环中发布数据
    ros::Duration(3).sleep();
    while (ros::ok())
    {
        count++;
        //msg.data = "hello";  第一步的
            //实现字符串拼接数字
              std::stringstream ss;  //定义拼接后的字符串
              ss <<"hello ---> " << count;    //拼接
              msg.data = ss.str();   //赋值

        pub.publish(msg);    //发布
            //添加日志
            ROS_INFO("发布的数据是：%s",ss.str().c_str()); 

        rate.sleep();  //休眠
        //回头一次
        ros::spinOnce();  //不过这里没有回调函数处理，所以不需要
    }
    





    return 0;
}