#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <octomap/math/Pose6D.h>
#include <octomap/math/Quaternion.h>
#include <octomap/math/Vector3.h>
#include <octomap/math/Utils.h>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>

#include <boost/thread/thread.hpp>

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/MapMetaData.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32.h>

#include <octomap_msgs/conversions.h>
#include <octomap_msgs/Octomap.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Point.h>
#include <octomap_ros/conversions.h>

using namespace std;
using namespace octomap;
using namespace octomath;
using namespace octomap_msgs;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "modMap");
  
  ros::NodeHandle node;
  
  ros::Rate rate(10.0);
  
  tf::TransformListener listener;
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  tf::StampedTransform stransform;
  tf::Quaternion q;
  
  tf::Transform modOffset;
  tf::Transform modTransform;
  tf::Transform dockOffset;

  //ros::Publisher path_pub = node.advertise<nav_msgs::Path>("/smorePath", 15);
  //ros::Publisher grid_pub = node.advertise<nav_msgs::OccupancyGrid>("/nav_map", 15);
  
  sleep(5);
  
  //ros::Subscriber sub = node.subscribe("/octomap_binary", 15, map_cb);
  //ros::Subscriber flag_sub = node.subscribe("/nbv_iter", 15, flag_cb);
  
  try{
    ros::Time gTime = ros::Time::now();
    listener.waitForTransform("camera_rgb_frame", "tag_5", gTime, ros::Duration(15.0));
    listener.lookupTransform("camera_rgb_frame", "tag_5", gTime, stransform);
  }
  catch (tf::TransformException &ex) {
    ROS_ERROR("%s",ex.what());
    ros::Duration(1.0).sleep();
  }
  point3d origin(stransform.getOrigin().x(), stransform.getOrigin().y(), stransform.getOrigin().z());
  
  cout << origin.x() << " : " << origin.y() << " : " << origin.z() << endl;
  
  modTransform.setOrigin(stransform.getOrigin());
  modTransform.setRotation(stransform.getRotation());
  
  q.setRPY(0, 0, 0);
  modOffset.setRotation(q);
  modOffset.setOrigin( tf::Vector3(0.0, 0.16, 0.0) );
  
  q.setRPY(0, 0, 0);
  dockOffset.setRotation(q);
  dockOffset.setOrigin( tf::Vector3(0.0, 0.06, 0.0) );
  
  cout << "Transforms Saved" << endl;
  
  while (ros::ok())
  {
    br.sendTransform(tf::StampedTransform(modTransform, ros::Time::now(), "camera_rgb_frame", "map"));
    rate.sleep();
    br.sendTransform(tf::StampedTransform(modOffset, ros::Time::now(), "tag_4", "goal"));
    br.sendTransform(tf::StampedTransform(dockOffset, ros::Time::now(), "tag_4", "dock"));
    ros::spinOnce();
  }
}