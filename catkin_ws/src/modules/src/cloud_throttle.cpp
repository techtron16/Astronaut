#include <stdio.h>
#include <iostream>
#include <std_msgs/Bool.h>
#include <sensor_msgs/PointCloud2.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>

bool flow = false;
ros::Publisher cloud_pub;

void switch_cb(const std_msgs::BoolConstPtr& msg)
{
	flow = msg->data;
	std::cout << flow << std::endl;
}

void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& msg)
{
	if (flow)
	{
		sensor_msgs::PointCloud2 cloud(*msg);
		cloud_pub.publish(cloud);
	}	
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "cloud_throttle");
	ros::NodeHandle node;
	ros::Rate rate(70.0);
	
	tf::TransformListener listener;
	static tf::TransformBroadcaster br;
	tf::Transform transform;
	tf::Transform transform2;
	tf::StampedTransform stransform;

	cloud_pub = node.advertise<sensor_msgs::PointCloud2>("/cloud_in", 15);

	ros::Subscriber switch_sub = node.subscribe<std_msgs::Bool>("/cloud_throttle", 15, switch_cb);
	ros::Subscriber cloud_sub = node.subscribe<sensor_msgs::PointCloud2>("/minnow/camera/depth/points", 15, cloud_cb);
	
	while (ros::ok())
	{
	  try
	  {
	    listener.waitForTransform("map", "odom", ros::Time::now(), ros::Duration(0.1));
	    listener.lookupTransform("map", "odom", ros::Time::now(), stransform);
	    
	    transform.setOrigin(stransform.getOrigin());
	    transform.setRotation(stransform.getRotation());
	  }
	  catch (tf::TransformException &ex)
	  {
	    
	  }
	  
	  /*try
	  {
	    listener.lookupTransform("odom", "base_footprint", ros::Time::now(), stransform);
	    
	    transform2.setOrigin(stransform.getOrigin());
	    transform2.setRotation(stransform.getRotation());
	  }
	  catch (tf::TransformException &ex)
	  {
	    
	  }*/
	  
	  br.sendTransform(tf::StampedTransform(transform, ros::Time::now() + ros::Duration(0.4), "map", "odom"));
	  //br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "odom", "base_footprint"));
	  rate.sleep();
	  ros::spinOnce();
	}

	ros::spin();
}
