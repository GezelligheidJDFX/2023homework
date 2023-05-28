#include "ros/ros.h"      //静态坐标系复制粘贴过来的，有部分修改
#include "tf2_ros/transform_listener.h"   //创建一个订阅者对象
#include "tf2_ros/buffer.h"   //把订阅到的数据缓存，与上一个联合使用
#include "geometry_msgs/PointStamped.h"  //创建一个坐标点数据对象
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"  //从一个坐标系里的一个坐标点转换到另一个坐标系里的点所用到的消息

/* 
    需求：订阅发布的坐标系相对关系，传入一个坐标点，调用 tf 实现转换

    流程：
       1.包含头文件；
       2.设置编码 节点初始化 NodeHandle(订阅方必须的)；---发布方节点句柄非必须
       3.创建订阅对象；---订阅坐标系相对关系
       4.组织一个坐标点数据；
       5.转换算法，需要调用TF内置实现；
       6.最后输出。
*/

int main(int argc, char *argv[])
{
    // 2.设置编码 节点初始化 NodeHandle；
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"dynamic_sub");
    ros::NodeHandle nh;

    //3.创建订阅对象；-----订阅坐标系相对关系
      // 3-1.创建一个 buffer 缓存
      tf2_ros::Buffer huan;         //不像静态坐标变换缓存里只有一个数据，动态变换中里的缓存有很多数据，是实时更新，且传过来存到缓存里是有延迟的，每个数据都有自己的时间戳
      // 3-2.再创建监听对象-----监听对象可以将订阅的数据传入buffer
      tf2_ros::TransformListener zwt(huan);

    //4.组织一个坐标点数据；
    geometry_msgs::PointStamped ps;

    //坐标系要修改
    ps.header.frame_id = "turtle1";
    ps.header.stamp = ros::Time(0.0);  //如果是now的话就是找也是这个时间戳的数据，会去验证时间是否对齐，如果相隔比较近，才会转换，设置成0.0，就是告诉计算机不用管了，直接转，不需要判断
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;

    //添加休眠 --- 可能存在订阅到的数据还未进入缓存，或者还没订阅到数据，这边就开始转换坐标系了，就会报错说 参考坐标系base_link 不存在未定义
    // ros::Duration(2).sleep();   -----休眠一会，跳过报错
    // 或者使用方案2：进行异常处理，使用 try 语句，接受报错 -----建议使用

    //5.转换算法，需要调用TF内置实现；
    ros::Rate r(10);
    while(ros::ok())   //循环发布应该是对应后面的动态坐标变换，因为传感器感应的障碍物的坐标点在实时变化
    {
        //异常处理方案2：
        try                   //理解为有错误信息就打印出来，然后等到有消息过来不报错为止
        {
            //核心代码 --- 将 坐标点对象ps 转换成相对于 小车坐标系base_link 的坐标点
            geometry_msgs::PointStamped ps_out;   //再创建一个相对于小车坐标系的坐标点对象来接收数据
            ps_out = huan.transform(ps,"zwt_world");  //两个参数，前者是要改变的坐标点信息，后者是要转换到的坐标系，返回值是输出的坐标点
            //理解为从缓存里拿数据用来转换，所以是缓存对象旗下的函数，且必须调用 "tf2_geometry_msgs/tf2_geometry_msgs.h"头文件

            //6.最后输出。
            ROS_INFO("转换后的坐标值：(%.2f,%.2f,%.2f),参考的坐标系：%s",    //字符串的打印就要转换成C风格的
                        ps_out.point.x,
                        ps_out.point.y,
                        ps_out.point.z,
                        ps_out.header.frame_id.c_str()
                        );
        }

        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            ROS_INFO("异常消息：%s",e.what());   //e.what()本身就是字符数组，就不需要转换处理了
        }    
        r.sleep();
        ros::spinOnce();
    }
    return 0;
}