#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

ros::Publisher pub;

void turtleCallback(const turtlesim::Pose::ConstPtr& msg) {
    geometry_msgs::Twist my_vel;
    my_vel.linear.x = 5.0;  
    my_vel.angular.z = 2.0;    
    pub.publish(my_vel);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_mover");
    ros::NodeHandle nh;

    pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

    ros::Subscriber sub = nh.subscribe("turtle1/pose", 10, turtleCallback);

    ros::spin();

    return 0;
}

