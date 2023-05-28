#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"

/*
    客户端：提交两个整数，并处理响应的结果。
    
       1.包含头文件；
       2.初始化ROS节点；
       3.创建节点句柄；
       4.创建一个客户端对象；
       5.提交请求并处理响应。

    实现参数的动态提交：
       1）格式：rosrun xxxxx xxxxx 12 34
       2) 节点执行时，需要获取命令中的参数，并组织进request

    问题：
       如果先启动客户端，那么会请求异常
    需求：
       如果先启动客户端，不要直接抛出异常，而是挂起，等服务器启动后，再正常请求
    解决方案：
       在ROS中内置了相关函数，这些函数可以让客户端启动后挂起，等待服务器启动
       client.waitForExistence
       ros::service::waitForService("服务话题")
*/

int main(int argc,char *argv[])   
{
    setlocale(LC_ALL,"");
    ROS_INFO("客户端");

    //优化实现，获取命令中参数
    if(argc != 3)   //参数里，程序本身是第一个，num1是第二个
    {
        ROS_INFO("提交的参数个数不对");
        return 1;
    }

    ros::init(argc,argv,"client");

    ros::NodeHandle nh;    //这里的Node和下面的ServiceClient可以当作“类”来理解，创建了一个类别，类别下实例化对象

    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::AddInts>("addInts");

    plumbing_server_client::AddInts ai; //创建话题下的对象

    //组织请求
    //ai.request.num1 = 100;  //对象下又有之前srv里的整形定义，既有request也有responser
    //ai.request.num2 = 200;  //提交名字为ai的数据，提交两个数字数据
    
    //优化实现
    ai.request.num1 = atoi(argv[1]);  
    ai.request.num2 = atoi(argv[2]);    //atoi函数是把字符串转换成整数类型

    //调用判断服务器状态的函数
    //函数1
       client.waitForExistence();   //挂起等待
    //函数2
       //ros::service::waitForService("addInts");  //功能一样，要输入被等待的服务

    //处理响应
    bool flag = client.call(ai);  //后面是访问服务器，把ai对象提交上去，再把响应拿到，
                                        //即responser的值已经封装进ai对象里了，然后就是用bool处理返回结果（0或1）

    if(flag)   //只有1和0的判断
    {
        ROS_INFO("响应成功！");
        ROS_INFO("响应结果 = %d",ai.response.sum);
    }else{
        ROS_INFO("响应失败...");
    }

    return 0;
}
