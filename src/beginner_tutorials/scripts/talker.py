#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int32
nu_id_digits = [2, 0, 2, 4, 9, 8, 0, 9, 1]
def talker(rate_hz):
    pub = rospy.Publisher('Karekeshova', Int32, queue_size=10)    
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(rate_hz)
    
    index = 0    
    while not rospy.is_shutdown():
        num = nu_id_digits[index]        
        rospy.loginfo(f"Publishing: {num}")
        pub.publish(num)
                
        index = (index + 1) % len(nu_id_digits)        
        
        rate.sleep()
        
if __name__ == '__main__':
    try:
        rate_hz = int(input("Enter rate (1 for 1Hz, 50 for 50Hz): "))          
        talker(rate_hz)
    except rospy.ROSInterruptException:     
        pass
