#include "ros/ros.h"                      //复制粘贴第二章实操里的服务调用板块
#include "turtlesim/Spawn.h"
/* 
   实现：是向服务端发送请求，生成一只新的乌龟
       话题：/spawn
       消息：turtlesim/Spawn

    1.包含头文件
    2.初始化 ROS 节点
    3.创建节点句柄
    4.创建客户端对象
    5.组织数据并发送
    6.处理响应  （数据什么时候发送，客户端是可控的，不需要回调函数处理，也不需要回旋函数了）
    6.spinOnce()
*/

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"tf_turtle");

    ros::NodeHandle j;

    ros::ServiceClient pge = j.serviceClient<turtlesim::Spawn>("/spawn");

    ros::service::waitForService("/spawn");

    turtlesim::Spawn spawn ;

    spawn.request.x = 1.0;
    spawn.request.y = 1.0;
    spawn.request.theta = 1.57;
    spawn.request.name = "turtle2";

    bool flag = pge.call(spawn);

    if(flag)
    {
        ROS_INFO("新的乌龟生成，名字: %s",spawn.response.name);
    }else{
        ROS_INFO("乌龟生成失败！！！");

    }

    return 0;
}