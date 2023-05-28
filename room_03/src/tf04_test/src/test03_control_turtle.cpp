#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"  //---6  新的头文件：多个坐标系的相对关系转换
#include "geometry_msgs/Twist.h"   //传播的消息类型要用到Twist相关的，比如线速度 角速度
/* 
    需求1：换算出 turtle1 相对于 turtle2 的关系
    需求2：计算角速度和线速度并发布
*/


/* 
    需求1：换算出 turtle1 相对于 turtle2 的关系
    需求2：计算角速度和线速度并发布
*/
int main(int argc, char *argv[])
{
    // 2.编码、初始化、NodeHandle
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"tfs_sub");
    ros::NodeHandle nh;

    // 3.创建订阅对象
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener zwt(buffer);

    // A.创建发布对象   ---头文件7
    ros::Publisher twist = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",100); //此话题也是键盘发布的话题，现在用新的运动代码来顶替

    // 4.编写解析逻辑

    ros::Rate r(10);
    while (ros::ok())
    {
        //核心
        try
        {
            geometry_msgs::TransformStamped son1Toson2;  // son1 相对于 son2
            son1Toson2 = buffer.lookupTransform("turtle2","turtle1",ros::Time(0));  
            // ROS_INFO("turtle1 相对于 turtle2 的信息：父级：%s, 子级：%s 偏移量(%.2f,%.2f,%.2f)",
            //              son1Toson2.header.frame_id.c_str(),  
            //              son1Toson2.child_frame_id.c_str(),   
            //              son1Toson2.transform.translation.x,
            //              son1Toson2.transform.translation.y,
            //              son1Toson2.transform.translation.z
            //              ); 

            // B.根据相对关系计算并组织速度消息
            geometry_msgs::Twist tmsg;
            /* 
                组织速度，只需要设置线速度的 x 与角速度的 z
                x = 系数 * 开方(y^2 + x^2)
                z = 系数 * 反正切(对边，邻边)  ---反正切就是正切的反函数，指的是弧度制的角度
            */
           tmsg.linear.x = 0.5 * sqrt(pow(son1Toson2.transform.translation.x , 2) + pow(son1Toson2.transform.translation.y , 2));
           tmsg.angular.z = 4 * atan2(son1Toson2.transform.translation.y , son1Toson2.transform.translation.x);

            // C.发布
            twist.publish(tmsg);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            ROS_INFO("错误提示：%s",e.what());
        }
        
        r.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
