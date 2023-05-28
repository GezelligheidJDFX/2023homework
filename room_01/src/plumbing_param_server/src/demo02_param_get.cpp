#include "ros/ros.h"

/*
    参数服务器操作之查询_C++实现:
    在 roscpp 中提供了两套 API 实现参数操作
    ros::NodeHandle

        param(键,默认值) 
            存在，返回对应结果，否则返回默认值

        getParam(键,存储结果的变量)
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamCached(键,存储结果的变量)--提高变量获取效率
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamNames(std::vector<std::string>)
            获取所有的键,并存储在参数 vector 中 

        hasParam(键)
            是否包含某个键，存在返回 true，否则返回 false

        searchParam(参数1，参数2)
            搜索键，参数1是被搜索的键，参数2存储搜索结果的变量

    ros::param ----- 与 NodeHandle 类似
*/

int main (int argc,char *argv[])
{
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"get_param_c");

    ros::NodeHandle nh;

    //查询参数

      //方案1：nh--------------------------------------------------------------------------

        //1.param
        double radius = nh.param("radius",0.5);  //接收的时候注意要返回的值的类型，且必须要接收
        ROS_INFO("radius = %.2f",radius);


        //2.getParam                    //与第一个类似，但可以判断是否接收成功
        double radius2 = 0.0;
        bool result1 = nh.getParam("radius",radius2);
        if(result1)
        {
            ROS_INFO("获取的半径是: %.2f",radius2);
        }else{
            ROS_INFO("被查询的变量不存在。");
        }
        

        //3.getParamCached    //提高运行效率，如果之前获取过，则会在缓存里面提取，没有就原路查找，效果跟第二个函数一样
        double radius3 = 0.0;
        bool result2 = nh.getParamCached("radius",radius3);
        if(result2)
        {
            ROS_INFO("获取的半径是: %.2f",radius2);
        }else{
            ROS_INFO("被查询的变量不存在。");
        }


        //4.getParamNames    
        std::vector<std::string> names; //创建一个对象来保存数据，vector可理解为数组类型，然后泛型是string类型的
        nh.getParamNames(names);  //获取所有参数名称并赋值给names
        for(auto &&name : names)  //for循环，元素是name，被遍历的是names
        {
            ROS_INFO("遍历到的元素: %s",name.c_str());
        }


        //5.hasParam
        bool flag1 = nh.hasParam("radius");
        bool flag2 = nh.hasParam("radiusxxx");
        ROS_INFO("radius 存在吗？ %d",flag1);
        ROS_INFO("radiusxxx 存在吗？ %d",flag2);


        //6.searchParam
        std::string key;
        nh.searchParam("radius",key);  //搜索的结果赋值给key，结果为：/radius，为字符串类型的
        ROS_INFO("搜索结果: %s",key.c_str());  //虽然key本身是字符串类型的，但在INFO这还要转为C风格的字符串

        std::string key2;
        nh.searchParam("radiusxxx",key2);  //搜索的结果赋值给key2，结果为：   。即输出空的内容
        ROS_INFO("搜索结果: %s",key2.c_str());  



      //方案2：ros::param---------------------------------------------------------------------------
        //ros::param::(param / get / getCached / getParamNames / has / search)
      ros::param::param("radius",0.3);



    return 0;
}