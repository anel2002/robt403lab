#include "ros/ros.h" 
#include "turtlesim/Pose.h" 
#include "geometry_msgs/Twist.h" 
#include "turtlesim/Spawn.h"   
 
ros::Publisher pub; 
 

void turtleCallback(const turtlesim::Pose::ConstPtr& msg) 
{ 
    ROS_INFO("Turtle Position: [x: %f, y: %f, theta: %f]", msg->x, msg->y, msg->theta); 
 
    geometry_msgs::Twist my_vel; 
    my_vel.linear.x = 10.0;  
    my_vel.angular.z = 10.0; 
 

    pub.publish(my_vel); 
} 
 
int main(int argc, char **argv) 
{ 
    ros::init(argc, argv, "turtle_listener"); 
    ros::NodeHandle nh; 
 

    ros::ServiceClient client1 = nh.serviceClient<turtlesim::Spawn>("/spawn"); 
 

    turtlesim::Spawn srv1; 
    srv1.request.x = 1.0; 
    srv1.request.y = 5.0; 
    srv1.request.theta = 0.0; 
    srv1.request.name = "Turtle_New"; 
 

    if (client1.call(srv1)) 
    { 
        ROS_INFO("New turtle spawned: %s", srv1.response.name.c_str()); 
    } 
    else 
    { 
        ROS_ERROR("Failed to spawn turtle."); 
    } 
 

    ros::Subscriber sub = nh.subscribe("/Turtle_New/pose", 10, turtleCallback); 
 

    pub = nh.advertise<geometry_msgs::Twist>("/Turtle_New/cmd_vel", 1); 
 
    ros::spin(); 
    return 0; 
}
