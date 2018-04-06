// This problam publishes randomly-generated velocity messages for turtlesim
#include <ros/ros.h>
#include <geometry_msgs/Twist.h> //For geometry_msgs::Twist
#include <stdlib.h> //for rand() and RAND_MAX

int main(int argc, char **argv)
{
	// Initalize the ROS system and become a node
	ros::init(argc, argv, "publish_velocity");
	ros::NodeHandle nh;

	// Create a publisher object (!expensive operation - avoid unecessary creations!).
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>
	("turtle1/cmd_vel", 1000);

	// Seed the RNG
	srand(time(0));

	// Loop at 2Hz until the node is shut down (Better than simple sleep, as it subtracts time from other computations)
	ros::Rate rate(2);
	while(ros::ok())
	{
		// Create and fill in the message. The other four
		// fields, which are ignored by turtlesim, default to 0
		geometry_msgs::Twist msg;
		msg.linear.x = double(rand())/double(RAND_MAX);
		msg.angular.z = 2*double(rand())/double(RAND_MAX) - 1;

		// Publish the message
		pub.publish(msg);

		// Send a message to rosout with the details.
		ROS_INFO_STREAM("Sending random velocity command:"
			<< " linear=" << msg.linear.x
			<< " angular=" << msg.angular.z);

		// Wait until it's tme for another iteration.
		rate.sleep();
	}
}