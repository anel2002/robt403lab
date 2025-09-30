#!/usr/bin/env python
import rospy
from std_msgs.msg import Float64

class MultiJointCommandFilter:
    def __init__(self):
        # Define joint names
        self.joint_names = ['joint1', 'joint2', 'joint3', 'joint4', 'joint5']

        # Store last received values per joint
        self.last_values = {}

        # Set up publishers and subscribers
        self.publishers = {}
        self.subscribers = {}

        for joint in self.joint_names:
            # Initial last value is None
            self.last_values[joint] = None

            # Publisher to the robot joint controller
            pub_topic = f"/robot/{joint}_position_controller/command"
            self.publishers[joint] = rospy.Publisher(pub_topic, Float64, queue_size=10)

            # Subscriber to the input command
            sub_topic = f"/{joint}_input"
            self.subscribers[joint] = rospy.Subscriber(sub_topic, Float64, self.make_callback(joint))

            rospy.loginfo(f"Set up filtering for {joint}")

    def make_callback(self, joint_name):
        def callback(msg):
            new_value = msg.data
            last_value = self.last_values[joint_name]

            if last_value is None or new_value > last_value:
                self.publishers[joint_name].publish(Float64(data=new_value))
                self.last_values[joint_name] = new_value
                rospy.loginfo(f"[{joint_name}] Published: {new_value}")
            else:
                rospy.loginfo(f"[{joint_name}] Ignored: {new_value} <= {last_value}")

        return callback

if __name__ == '__main__':
    rospy.init_node('multi_joint_filter_node')
    MultiJointCommandFilter()
    rospy.spin()

