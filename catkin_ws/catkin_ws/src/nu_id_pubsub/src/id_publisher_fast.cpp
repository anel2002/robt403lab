#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <vector>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "id_publisher_fast");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::Int32>("Utepbergen", 10);

    std::vector<int> id_digits = {2, 0, 2, 1, 4, 7, 0, 8, 9};

    ros::Rate loop_rate(50);  

    size_t index = 0;
    while (ros::ok())
    {
        std_msgs::Int32 msg;
        msg.data = id_digits[index];

        ROS_INFO("Publishing (50Hz): %d", msg.data);
        pub.publish(msg);


        loop_rate.sleep();

        index = (index + 1) % id_digits.size();
    }

    return 0;
}

