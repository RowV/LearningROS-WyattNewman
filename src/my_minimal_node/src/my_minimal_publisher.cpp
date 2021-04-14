#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main (int argc, char **argv){

	ros::init(argc, argv, "minimal_publisher");
	ros::NodeHandle n;

	ros::Publisher my_publisher_obj = n.advertise <std_msgs::Float64> ("test_topic", 1); // test_topic = name of topic. 1 is buffer size

	std_msgs::Float64 op_data;

	op_data.data = 0.0;
	while (ros::ok())
	{
		op_data.data = op_data.data + 0.001;
		my_publisher_obj.publish(op_data);
	}
	return 0;
}
