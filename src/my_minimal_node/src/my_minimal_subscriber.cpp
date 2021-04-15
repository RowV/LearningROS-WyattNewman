#include <ros/ros.h>
#include <std_msgs/Float64.h>

void subsCallback(const std_msgs::Float64& message_holder)
{
        ROS_INFO("Recieved value is: %f", message_holder.data);

}

int main (int argc, char **argv){

	ros::init(argc, argv, "minimal_subscriber");
	ros::NodeHandle n;

	// test_topic = name of topic. 1 is buffer size
	ros::Subscriber my_subscriber_obj = n.subscribe("test_topic", 1, subsCallback);
        ros::spin();

	return 0;
}
