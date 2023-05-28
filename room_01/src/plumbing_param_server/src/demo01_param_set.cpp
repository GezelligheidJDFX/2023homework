#include "ros/ros.h"

/*
    需要实现参数的新增与修改
      需求：
         首先设置机器人的共享参数，如类型、尺寸(0.15m)
         再修改其半径(0.2m)
      实现：
         ros::NodeHandle
             setParam("键"，值)
         ros::param
             set("键"，值)
      修改：
          只需要继续调用同一个设置参数的函数，保证名字相同，值会被新值覆盖
*/

int main (int argc,char *argv[])
{
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"set_param_c");

    ros::NodeHandle nh;

    //参数增---------------------------------------

      //方案1：nh
      nh.setParam("type","xiaozhang");  //字符串类型的数据也要加双引号“”
      nh.setParam("radius",0.15);

      //方案2：ros::param
      ros::param::set("type_param","xiaozhang");
      ros::param::set("radius_param",0.15);


    //参数改---------------------------------------//就是重新設置，实质上函數没变
    
      //方案1：nh
      nh.setParam("radius",0.2);
      
      //方案2：ros::param
      ros::param::set("radius_param",0.25);

    return 0;
}