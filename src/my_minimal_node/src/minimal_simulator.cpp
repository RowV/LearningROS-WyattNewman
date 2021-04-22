#include <ros/ros.h>
#include <std_msgs/Float64.h>

std_msgs::Float64 g_velocity;
std_msgs::Float64 g_force;

void get_force_callback(const std_msgs::Float64 & message_holder)
{
  
 ROS_INFO("Input Force F = %f", message_holder.data);
 g_force.data = message_holder.data;

}

int main(int argc, char **argv)
{
 ros::init(argc,argv, "minimal_simulator");
 ros::NodeHandle n;
 
 ros::Subscriber my_force_subscriber = n.subscribe("force_cmd", 1, get_force_callback);
 ros::Publisher  my_simulator_output = n.advertise <std_msgs::Float64> ("velocity_cmd", 1);

 double mass        = 1.0;
 double dt          = 0.01; //10ms integration
 double sample_rate = 1.0/dt;
 
 ros::Rate naptime(sample_rate);
 g_velocity.data = 0.0;
 g_force.data    = 0.0;

 while(ros::ok())
 {
   g_velocity.data     = g_velocity.data + ((g_force.data/mass)*dt);
   my_simulator_output.publish(g_velocity); 

   ROS_INFO("Velocity = %f \n", g_velocity.data);  
   ros::spinOnce();
   naptime.sleep();
 } 
 
 return 0;
}
