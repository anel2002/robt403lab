#include "ros/ros.h"
#include "turtlesim/Pose.h"

void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
    ROS_INFO("Turtle Position: [x: %f, y: %f, theta: %f]", msg->x, msg->y, msg->theta);
}

int main(int argc, char **argv)
{    
    ros::init(argc, argv, "turtle_listener");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/turtle1/pose", 10, turtleCallback);
    
    ros::spin(); 
    return 0;
}
