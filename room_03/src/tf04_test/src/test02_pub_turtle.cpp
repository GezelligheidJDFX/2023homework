#include "ros/ros.h"                        //复制粘贴此章节 tf02_dynamic 里的 demo01
#include "turtlesim/Pose.h"              
#include "tf2_ros/transform_broadcaster.h"   
#include "geometry_msgs/TransformStamped.h"  
#include "tf2/LinearMath/Quaternion.h"

//要扩大一个变量的作用域，需要声明变量接收传递的数据
std::string turtle_name;

void dopose (const turtlesim::Pose::ConstPtr& posemsg)    
{                                                         
    //获取位姿信息，转换成坐标系相对关系（核心），并发布        

    //a.创建发布对象；---头文件3                             
    static tf2_ros::TransformBroadcaster zwt ;

    //b.组织被发布的数据；---头文件4
    geometry_msgs::TransformStamped posemsg2;
    posemsg2.header.frame_id = "zwt_world";
    posemsg2.header.stamp = ros::Time::now();

    //关键点2：动态传入
    // posemsg2.child_frame_id = "turtle1"; 
    posemsg2.child_frame_id = turtle_name;  //不是静态不变的字符串了，所以要去掉双引号，改成可变的变量

    //坐标系偏移量设置
    posemsg2.transform.translation.x = posemsg->x;
    posemsg2.transform.translation.y = posemsg->y;
    posemsg2.transform.translation.z = 0;    

    //坐标系四元数 ---需要转换，头文件5
    tf2::Quaternion four1;
    four1.setRPY(0,0,posemsg->theta);

    posemsg2.transform.rotation.x = four1.getX();
    posemsg2.transform.rotation.y = four1.getY();
    posemsg2.transform.rotation.z = four1.getZ();
    posemsg2.transform.rotation.w = four1.getW();

    //c.发布
    zwt.sendTransform(posemsg2);
}

int main(int argc, char *argv[])
{
    //2.设置编码 初始化 NodeHandle
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"test_pub");
    ros::NodeHandle nh;

    /* 
          解析 launch 文件通过 args 传入的参数
    */
   if (argc != 2)      //这个节点要分别开两次，所以每开一次就只需要传入一个参数，而程序本身算第一个参数，所以是 2
   {
      ROS_ERROR("请传入一个参数");
      return 1;
   }else{
       turtle_name = argv[1];   //这里用 argv 传参，而不是 argc ，因为 argc 指的是参数个数，而 argv 是具体参数构成的数组
   }
    
    //3.创建订阅对象，订阅 /turtle1/pose
    //关键点1：订阅的话题名称，turtle1 turtle2 是动态传入的
    ros::Subscriber jdfx = nh.subscribe(turtle_name + "/pose",100,dopose);   //本来是 /turtle1/pose 订阅到的是有前缀turtle1的pose位姿信息

    //4.回调函数处理订阅的消息：将位姿信息转换成坐标相对关系并发布（关注）

    //5.spin()
    ros::spin();

    return 0;
}
