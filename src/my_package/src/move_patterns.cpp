#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <unistd.h> 

void moveStraight(ros::Publisher pub, double speed, double duration) {
    geometry_msgs::Twist vel;
    vel.linear.x = speed;
    vel.angular.z = 0.0;
    pub.publish(vel);
    ros::Duration(duration).sleep();
    vel.linear.x = 0.0;
    pub.publish(vel);
}

void rotate(ros::Publisher pub, double angular_speed, double duration) {
    geometry_msgs::Twist vel;
    vel.linear.x = 0.0;
    vel.angular.z = angular_speed;
    pub.publish(vel);
    ros::Duration(duration).sleep();
    vel.angular.z = 0.0;
    pub.publish(vel);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "move_patterns");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle_Anel/cmd_vel", 10);

    ros::Duration(2.0).sleep(); 

    ROS_INFO("Moving in square...");

    for (int i = 0; i < 4; i++) {
        moveStraight(pub, 2.0, 1.5);
        rotate(pub, 1.57, 1.0); // ~90 degrees
    }

    ros::Duration(2.0).sleep();

    ROS_INFO("Moving in triangle...");

    for (int i = 0; i < 3; i++) {
        moveStraight(pub, 2.0, 1.7);
        rotate(pub, 2.1, 1.0); // ~120 degrees
    }

    ROS_INFO("Done.");

    return 0;
}

