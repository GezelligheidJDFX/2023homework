#include "ros/ros.h"
#include "plumbing_head_src/hello.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "hello_head_src");
    
    //函数调用
    hello_ns::MyHello my_hello;
    my_hello.run();
    
    return 0;
}
