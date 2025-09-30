#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float64
import time

class SquareWavePublisher:
    def __init__(self):
        rospy.init_node('square_wave_publisher_node')
        
        # Publishers for base and end-effector joints
        self.pub_joint1 = rospy.Publisher('/robot/joint1_position_controller/command', Float64, queue_size=10)
        self.pub_joint5 = rospy.Publisher('/robot/joint5_position_controller/command', Float64, queue_size=10)

        self.rate = rospy.Rate(0.5)  # One toggle every 2 seconds
        self.high = True

        rospy.loginfo("Square wave publisher started.")

    def run(self):
        while not rospy.is_shutdown():
            if self.high:
                value = 1.0
            else:
                value = 0.0

            # Publish to both joints
            self.pub_joint1.publish(Float64(data=value))
            self.pub_joint5.publish(Float64(data=value))
            rospy.loginfo(f"Published {value} to joint1 and joint5")

            self.high = not self.high
            self.rate.sleep()

if __name__ == '__main__':
    try:
        node = SquareWavePublisher()
        node.run()
    except rospy.ROSInterruptException:
        pass
3
