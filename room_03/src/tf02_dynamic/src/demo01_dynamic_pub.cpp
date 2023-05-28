#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"   //与静态坐标系引用的头文件不同，少了static
#include "geometry_msgs/TransformStamped.h"  //这里也是不同的，多了Stamped
#include "tf2/LinearMath/Quaternion.h"

/* 
   发布方：需要订阅乌龟的位姿信息，转换成相对于窗体的坐标关系，并发布
   准备：
      话题：turtle1/pose
      消息：turtlesim/Pose  ---大小写区分
    流程：
      1.包含头文件
      2.设置编码 初始化 NodeHandle
      3.创建订阅对象，订阅 /turtle1/pose
      4.回调函数处理订阅的消息：将位姿信息转换成坐标相对关系并发布（关注）
      5.spin()
*/
  //要引用此话题下的消息类型的数据，头文件2
void dopose (const turtlesim::Pose::ConstPtr& posemsg)    //订阅的话题是 pose ，话题里的消息类型是 Pose ，通信用 Pose 传递
{                                                         //然后接收Pose后回调，回调里引用赋予给新的变量 posemsg
    //获取位姿信息，转换成坐标系相对关系（核心），并发布          //重要的是 Pose 是个类，可通过 rosmsg info 来查看它旗下管理的变量或函数
    //a.创建发布对象；---头文件3                             //然后通过引用后，新变量也有了管理 Pose旗下小弟们的能力，就可以通过指针来拿到对应小弟的数据
    static tf2_ros::TransformBroadcaster zwt ;
    //b.组织被发布的数据；---头文件4
    geometry_msgs::TransformStamped posemsg2;
    posemsg2.header.frame_id = "zwt_world";
    posemsg2.header.stamp = ros::Time::now();
    posemsg2.child_frame_id = "turtle1"; //自定义的名称，在rviz中构建一个新的坐标，链接接收到的位姿信息
    //坐标系偏移量设置
    posemsg2.transform.translation.x = posemsg->x;
    posemsg2.transform.translation.y = posemsg->y;
    posemsg2.transform.translation.z = 0;    
    //坐标系四元数 ---需要转换，头文件5
    /* 
        位姿信息中没有四元数，但是有个偏航角度，又已知乌龟是 2D ，没有翻滚与俯仰角度，所以可以得出乌龟的欧拉角：0 0 theta    
    */
    tf2::Quaternion four1;
    four1.setRPY(0,0,posemsg->theta);

    posemsg2.transform.rotation.x = four1.getX();
    posemsg2.transform.rotation.y = four1.getY();
    posemsg2.transform.rotation.z = four1.getZ();
    posemsg2.transform.rotation.w = four1.getW();

    //c.发布
    zwt.sendTransform(posemsg2);
}

int main(int argc, char  *argv[])
{
    //2.设置编码 初始化 NodeHandle
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"dynamic_pub");
    ros::NodeHandle nh;

    //3.创建订阅对象，订阅 /turtle1/pose
    ros::Subscriber jdfx = nh.subscribe("/turtle1/pose",100,dopose);
    //4.回调函数处理订阅的消息：将位姿信息转换成坐标相对关系并发布（关注）
    //5.spin()
    ros::spin();

    return 0;
}
