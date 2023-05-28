#include "ros/ros.h"
#include "rosbag/bag.h"
#include "rosbag/view.h"
#include "std_msgs/String.h"

/* 
    需求：使用 rosbag 读取磁盘上的bag文件
    流程：
       1.导包
       2.初始化
       3.创建 rosbag 对象
       4.打开文件流（以读的方式打开）
       5.读数据
       6.关闭文件流
*/

int main(int argc, char *argv[])
{
    // 2.初始化
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"bag_read");
    ros::NodeHandle nh;

    // 3.创建 rosbag 对象
    rosbag::Bag zwt_read;

    // 4.打开文件流（以读的方式打开）
    zwt_read.open("zwt.bag",rosbag::BagMode::Read);    // 可以理解为对象已经读取了文件里的数据，已经包含在对象里面了

    // 5.读数据
    // 取出话题、时间戳和消息内容  ---rosbag::View
    // 可以先获取消息的集合，再迭代取出消息的字段  ---会先用view函数去读取数据，把数据封装进一个集合，然后里面有迭代器，直接遍历取出要的数据就行
    // 用 for 循环来遍历每一个数据                                                  //迭代器可理解为提供数据拿取的接口
    for (auto &&m :  rosbag::View(zwt_read) )    //forrange  &&后面的意思是给每个元素取个名       
    {
        //解析
        std::string topic = m.getTopic();   //创建一个 string 对象来接收话题名称 topic  是 C++ 里的，要与 std_msgs 区分开
        ros::Time t0 = m.getTime();
        std_msgs::StringPtr p = m.instantiate<std_msgs::String>();              //要包含头文件 std_msgs   返回值是指针类型的
        ROS_INFO("解析的内容，话题：%s ,时间戳：%.2f ,消息值：%s",
                                 topic.c_str(),
                                 t0.toSec(),
                                 p->data.c_str()
                                 );
    }
     
    // 6.关闭文件流
    zwt_read.close();

    return 0;
}
