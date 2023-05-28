#include "ros/ros.h"

/* 
   实现：修改参数服务器中 turtlesim 背景色相关的参数

    1.初始化 ROS 节点
    2.不一定需要创建节点句柄（和后续API有关）
    3.修改参数
*/

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"change_bgColor");

    //方案一：ROS下的函数
    // ros::param::set("/turtlesim/background_r",255);
    // ros::param::set("/turtlesim/background_g",0);
    // ros::param::set("/turtlesim/background_b",0);

    //方案二：节点句柄
    ros::NodeHandle h("turtlesim"); //把最上层的命名空间拿到句柄定义里来，提高后面打码效率，注意“/”就可以去掉了

    h.setParam("background_r",255);
    h.setParam("background_g",255);
    h.setParam("background_b",255);

    return 0;
}