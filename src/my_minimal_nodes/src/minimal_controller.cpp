#include <ros/ros.h>
#include <std_msgs/Float64.h>

std_msgs::Float64 g_velocity;
std_msgs::Float64 g_vel_cmd;
std_msgs::Float64 g_force;

void getVelState( const std_msgs::Float64 & message_holder)
{ 
  g_velocity = message_holder;

}

void getVelCmd( const std_msgs::Float64 & message_holder)
{
  g_vel_cmd = message_holder;
}

int main (int argc, char **argv)
{
 ros::init(argc, argv, "minimal_controller");
 ros::NodeHandle nh;

 ros::Subscriber velocity_sub_obj = nh.subscribe("velocity", 1, getVelState); 
 ros::Subscriber vel_cmd_sub_obj  = nh.subscribe("vel_cmd", 1, getVelCmd);

 ros::Publisher force_cmd_output  = nh.advertise <std_msgs::Float64> ("force_cmd",1);
 
 double Kv = 1.0; // velocity feedbak
 double dt = 0.1; // 10hz controller smaple rate

 double sample_rate = 1.0/dt; //update frequncey

 ros::Rate naptime(sample_rate);
 g_velocity.data = 0.0;
 g_force.data    = 0.0;
 g_vel_cmd.data  = 0.0;
 
 double vel_error= 0.0;

 while(ros::ok())
 { 
   vel_error = g_vel_cmd.data - g_velocity.data;
   g_force.data = Kv*vel_error;
   
   force_cmd_output.publish(g_force);
   ROS_INFO("Force command = %f",g_force.data);
   
   ros::spinOnce();
   naptime.sleep();
 }
}
