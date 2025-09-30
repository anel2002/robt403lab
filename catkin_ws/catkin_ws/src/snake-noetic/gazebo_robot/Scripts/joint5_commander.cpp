#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main(int argc, char **argv)
{
    // Initialize ROS node
    ros::init(argc, argv, "joint5_commander");

    // Create node handle
    ros::NodeHandle nh;

    // Publisher for joint 5
    ros::Publisher pub5 = nh.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 10);

    // Wait for publisher to connect
    ros::Duration(1.0).sleep();

    // Create message
    std_msgs::Float64 msg;
    msg.data = 1;  // Target joint angle in radians

    ros::Rate rate(10);  // 10 Hz

    while (ros::ok())
    {
        pub5.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

