#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_spawner");
    ros::NodeHandle nh;

    ros::ServiceClient client1 = nh.serviceClient<turtlesim::Spawn>("/spawn");

    turtlesim::Spawn srv1;
    srv1.request.x = 1.0;
    srv1.request.y = 5.0;
    srv1.request.theta = 0.0;
    srv1.request.name = "Turtle_Aray";  

    if (client1.call(srv1)) {
        ROS_INFO("Spawned turtle named: %s", srv1.response.name.c_str());
    } else {
        ROS_ERROR("Failed to call service /spawn");
    }

    return 0;
}

