#include "ros/ros.h" 
#include "geometry_msgs/Twist.h" 
#include "turtlesim/TeleportAbsolute.h" 
#include "turtlesim/Kill.h" 
#include "turtlesim/Spawn.h" 
#include <cmath>
double pi = M_PI; 



struct Point { 
    double x, y; 
}; 
 
Point square_corners[4] = { 
    {1.0, 1.0}, 
    {9.0, 1.0}, 
    {9.0, 9.0}, 
    {1.0, 9.0} 
}; 
 
Point triangle_corners[3] = { 
    {1.0, 1.0},   
    {9.0, 1.0},   
    {1.0, 9.0}   
}; 
 

void teleportTurtle(ros::NodeHandle &nh, double x, double y, double theta) { 
    ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute"); 
    turtlesim::TeleportAbsolute srv; 
    srv.request.x = x; 
    srv.request.y = y; 
    srv.request.theta = theta; 
 
    if (teleport_client.call(srv)) { 
        ROS_INFO("Teleported to (%.2f, %.2f)", x, y); 
    } else { 
        ROS_ERROR("Failed to teleport the turtle."); 
    } 
} 
 

void moveTo(ros::Publisher pub, double speed, double time) { 
    geometry_msgs::Twist vel_msg; 
    vel_msg.linear.x = speed; 
    vel_msg.angular.z = 0.0; 
 
    ros::Rate rate(10); 
    double t0 = ros::Time::now().toSec(); 
    double t1; 
 
    while (ros::ok()) { 
        t1 = ros::Time::now().toSec(); 
        if (t1 - t0 >= time) break; 
        pub.publish(vel_msg); 
        rate.sleep(); 
    } 
 
    vel_msg.linear.x = 0.0; 
    pub.publish(vel_msg);  
} 
 

void rotateTurtle(ros::Publisher pub, double angular_speed, double time) { 
    geometry_msgs::Twist vel_msg; 
    vel_msg.linear.x = 0.0; 
    vel_msg.angular.z = angular_speed; 
 
    ros::Rate rate(10); 
    double t0 = ros::Time::now().toSec(); 
    double t1; 
 
    while (ros::ok()) { 
        t1 = ros::Time::now().toSec(); 
        if (t1 - t0 >= time) break; 
        pub.publish(vel_msg); 
        rate.sleep(); 
    } 
 
    vel_msg.angular.z = 0.0; 
    pub.publish(vel_msg);  
} 
 

void moveSquare(ros::NodeHandle &nh, ros::Publisher pub) { 
    teleportTurtle(nh, square_corners[0].x, square_corners[0].y, 0.0); 
    for (int i = 1; i < 4; i++) { 
        moveTo(pub, 4.0, 2.0); 
        rotateTurtle(pub, pi/2, 1); 
    } 
    moveTo(pub, 4.0, 2.0);  
} 
 

void moveTriangle(ros::NodeHandle &nh, ros::Publisher pub) { 
    teleportTurtle(nh, triangle_corners[0].x, triangle_corners[0].y, 0.0); 
    for (int i = 1; i < 3; i++) { 

	moveTo(pub, 4.0, 2); 
        rotateTurtle(pub, pi/4, 2); 
    } 

    rotateTurtle(pub, pi/8, 2);

    moveTo(pub, 4, 2*sqrt(2));  
} 
 
int main(int argc, char **argv) { 
    ros::init(argc, argv, "turtle_exact_trajectory"); 
    ros::NodeHandle nh; 
 

    ros::ServiceClient kill_client = nh.serviceClient<turtlesim::Kill>("/kill"); 
    turtlesim::Kill kill_srv; 
    kill_srv.request.name = "turtle1"; 
 
    if (kill_client.call(kill_srv)) { 
        ROS_INFO("Killed existing turtle."); 
    } else { 
        ROS_WARN("No existing turtle to kill."); 
    } 
 

    ros::ServiceClient spawn_client = nh.serviceClient<turtlesim::Spawn>("/spawn"); 
    turtlesim::Spawn spawn_srv; 
    spawn_srv.request.x = 5.0; 
    spawn_srv.request.y = 5.0; 
    spawn_srv.request.theta = 0.0; 
    spawn_srv.request.name = "turtle1"; 
 
    if (spawn_client.call(spawn_srv)) { 
        ROS_INFO("Spawned new turtle at center."); 
    } else { 
        ROS_ERROR("Failed to spawn turtle."); 
    } 
 
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10); 
    ros::Duration(2.0).sleep();
 
 
    ROS_INFO("Moving in a Square..."); 
    moveSquare(nh, pub); 
 
    ros::Duration(2.0).sleep(); 
 
    ROS_INFO("Moving in a Triangle...");
    moveTriangle(nh, pub); 
 
    return 0; 
}
