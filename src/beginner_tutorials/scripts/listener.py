#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int32

def callback(data):
    rospy.loginfo(f"I heard: {data.data}")

def listener():
    rospy.init_node('listener', anonymous=True)    
    rospy.Subscriber("Karekeshova", Int32, callback)
    rospy.spin()
    
if __name__ == '__main__':
    listener()
