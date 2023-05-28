#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"    //有关TF的通信内容，创建一个发布者对象
#include "geometry_msgs/Transform.h"     //创建传输信息的对象，使用对象下的各个功能
#include "tf2/LinearMath/Quaternion.h"   //欧拉角转换成四元数

/* 
    需求：发布两个坐标系的相对关系

    流程：
       1.包含头文件；
       2.设置编码 节点初始化 NodeHandle；
       3.创建发布对象；
       4.组织被发布的消息；
       5.发布数据；
       6.spin();
*/

int main(int argc, char *argv[])
{
    // 2.设置编码 节点初始化 NodeHandle；
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_pub");
    ros::NodeHandle nh;

    // 3.创建发布对象；
    tf2_ros::StaticTransformBroadcaster jdfx;

    // 4.组织被发布的消息；
    geometry_msgs::TransformStamped tfmsg;   //TransformStamped 是用来获得两个坐标系的相对关系的

    tfmsg.header.seq = 100;   //随便设置一个
    tfmsg.header.stamp = ros::Time::now();
    tfmsg.header.frame_id = "base_link";  //相对坐标系关系中被参考的那一个
    tfmsg.child_frame_id = "laser";

    tfmsg.transform.translation.x = 0.2;
    tfmsg.transform.translation.y = 0.0;
    tfmsg.transform.translation.z = 0.5;

    //需要根据欧拉角转换       //欧拉角就是之前的飞机偏航旋转角那些，沿着某个轴旋转，为弧度制
    tf2::Quaternion four;  //创建 四元数 对象
    four.setRPY(0,0,0);   //向该对象设置欧拉角，这个对象可以将欧拉角转换成四元数,(0,0,0)表示是正放的，各个方向无任何旋转
    tfmsg.transform.rotation.x = four.getX();
    tfmsg.transform.rotation.y = four.getY();
    tfmsg.transform.rotation.z = four.getZ();  //通过别的封装的函数转换后，就可以调用其转换后的数值了
    tfmsg.transform.rotation.w = four.getW();

    // 5.发布数据；
    jdfx.sendTransform(tfmsg);

    // 6.spin();
    ros::spin();

    return 0;
}
