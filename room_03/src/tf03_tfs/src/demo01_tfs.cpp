#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"  //---6  新的头文件：多个坐标系的相对关系转换
/* 
    订阅方实现：1.计算 son1 与 son2 的相对关系  2.计算 son1 中某个坐标点在 son2 中的坐标值

    流程：
       1.包含头文件
       2.编码、初始化、NodeHandle
       3.创建订阅对象
       4.编写解析逻辑
       5.spinOnce()
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

    // 4.编写解析逻辑

    // 创建坐标点
    geometry_msgs::PointStamped psAtSon1;

    psAtSon1.header.frame_id = "son1";
    psAtSon1.header.stamp = ros::Time::now();
    psAtSon1.point.x = 1.0;
    psAtSon1.point.y = 2.0;
    psAtSon1.point.z = 3.0;

    ros::Rate r(10);
    while (ros::ok())
    {
        //核心
        try
        {
            //1.计算 son1 与 son2 的相对关系  ---头文件6
            /* 
                需求：A 相对于 B 的坐标系关系

                参数1：目标坐标系  B
                参数2：源坐标系    A
                参数3：ros::Time(0)  取间隔最短的两个坐标关系帧计算相对关系
                返回值：geometry_msgs::TransformStamped 源相对于目标坐标系的相对关系
            */
            geometry_msgs::TransformStamped son1Toson2;  // son1 相对于 son2
            son1Toson2 = buffer.lookupTransform("son2","son1",ros::Time(0));  //因为son1和son2分别与world的相对关系的发布可能有很多个，时间参数为零的意思是，找到时间最相近的两个
            ROS_INFO("son1 相对于 son2 的信息：父级：%s, 子级：%s 偏移量(%.2f,%.2f,%.2f)",
                         son1Toson2.header.frame_id.c_str(),  //son2
                         son1Toson2.child_frame_id.c_str(),   //son1
                         son1Toson2.transform.translation.x,
                         son1Toson2.transform.translation.y,
                         son1Toson2.transform.translation.z
                         ); 

            //2.计算 son1 中某个坐标点在 son2 中的坐标值
            geometry_msgs::PointStamped psAtSon2;   
            psAtSon2 = buffer.transform(psAtSon1,"son2");            
            ROS_INFO("坐标点在 Son2 中的值(%.2f,%.2f,%.2f)",    
                        psAtSon2.point.x,
                        psAtSon2.point.y,
                        psAtSon2.point.z
                        );
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
