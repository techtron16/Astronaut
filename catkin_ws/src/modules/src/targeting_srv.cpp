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

#include <sensorCell.h>
#include <MinHeap.h>
#include <InfoNode.h>
#include "../../../devel/include/modules/target_req.h"

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>
#include <../../opt/ros/indigo/include/nav_msgs/OccupancyGrid.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/MapMetaData.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Int32.h>

#include <visualization_msgs/Marker.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/String.h>

#include <octomap_msgs/conversions.h>
#include <octomap_msgs/Octomap.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Vector3.h>
#include <octomap_ros/conversions.h>
#include <actionlib_msgs/GoalID.h>

#include <tf/LinearMath/Vector3.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <apriltags_ros/AprilTagDetection.h>
#include <apriltags_ros/AprilTagDetectionArray.h>

#include "modules/target_req.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace std;
using namespace octomap;
using namespace octomath;
using namespace octomap_msgs;

bool mapReceived;
Octomap mapMsg;
double res = 0.02;
double rFactor = 1 / res;
tf::Quaternion q;
move_base_msgs::MoveBaseGoal goal;
bool nbvReceived = false;
bool pinkReceived = false;
bool goalRunning = false;
nav_msgs::OccupancyGrid map2d;
nav_msgs::OccupancyGrid bloatMap;
bool gridReceived = false;

ros::Publisher path_pub;
ros::Publisher grid_pub;

void grid_cb(const nav_msgs::OccupancyGridConstPtr& grid)
{
  map2d = *grid;
  gridReceived = true;
  //cout << "Got emmm" << endl;
}

bool target_req_cb(modules::target_req::Request  &req, modules::target_req::Response &res)
{
  ROS_INFO("Request Received");
  
  tf::TransformListener listener;
  tf::Transform transform;
  tf::StampedTransform stransform;
  tf::Quaternion q;
  
  static tf::TransformBroadcaster br;
  
  ros::Rate rate(10.0);
    
  double maxReach = 0.7;
  double carReach = 0.06;
  
  /*for (int i = 1; i < 5; i++)
  {
    try{
      ros::Time gTime = ros::Time::now() - ros::Duration(1.0);
      listener.waitForTransform("map", "pinkObj", gTime, ros::Duration(2));
      listener.lookupTransform("map", "pinkObj", gTime, stransform);
      break;
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      pinkReceived = false;
    }
  }*/
  
  double xObj = req.request.position.x;
  double yObj = req.request.position.y;
  
  tf::Vector3 objVec(xObj, yObj, 0);
  
  while (true)
  {
    try{
      ros::Time gTime = ros::Time::now();
      listener.waitForTransform("map", "base_footprint", gTime, ros::Duration(1));
      listener.lookupTransform("map", "base_footprint", gTime, stransform);
      break;
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
    }
  }
  
  //--------------
  //Bloat Map
  //--------------
  
  ROS_INFO("Check for valid map");
  while (map2d.data.size() == 0)
  {
    ros::spinOnce();
    rate.sleep();
  }
  ROS_INFO("Valid map");
  
  double robotRad = 0.3;
  bloatMap = map2d;
  
  nav_msgs::MapMetaData mapMeta = map2d.info;
  int rangeX = mapMeta.width;
  int rangeY = mapMeta.height;
  double minX = mapMeta.origin.position.x;
  double minY = mapMeta.origin.position.y;
  double mRes = mapMeta.resolution;
  
  for (int x = 0; x < rangeX; x++)
  {
    for (int y = 0; y < rangeY; y++)
    {
      int index = rangeX * y + x;
      
      point3d coord(double(x) * mRes + mapMeta.origin.position.x, double(y) * mRes + mapMeta.origin.position.y, 0);
      
      if (int(map2d.data[index]) > 50)
      {
	for (double offX = -robotRad; offX <= robotRad; offX += mRes)
	{
	  for (double offY = -robotRad; offY <= robotRad; offY += mRes)
	  {
	    if (sqrt(pow(offX, 2) + pow(offY, 2)) <= robotRad)
	    {
	      int xInd = round((coord.x() + offX - minX) / mRes);
	      int yInd = round((coord.y() + offY - minY) / mRes);
	      
	      if (xInd >= 0 && xInd < rangeX && yInd >= 0 && yInd < rangeY && abs(xInd) + abs(yInd) > 0)
	      {
		int offIdx = yInd * rangeX + xInd;
		
		bloatMap.data[offIdx] = 99;
	      }
	    }
	  }
	}
      }
    }
  }
  
  grid_pub.publish(bloatMap);
  
  //--------------
  //Finished Bloating Map
  //--------------
  
  double xRobot = stransform.getOrigin().getX();
  double yRobot = stransform.getOrigin().getY();
  
  tf::Vector3 robotVec(xRobot, yRobot, 0);
  
  cout << "Robot Vector: " << robotVec.getX() << ", " << robotVec.getY() << endl;
  
  robotVec -= objVec;
  
  cout << "Robot Relative: " << robotVec.getX() << ", " << robotVec.getY() << endl;
  
  double minDistance = maxReach;
  tf::Vector3 minCell(0, 0, 0);
  tf::Vector3 cellVec(0, 0, 0);
  
  for (int i = 0; i < bloatMap.info.height; i++)
  {
    for (int j = 0; j < bloatMap.info.width; j++)
    {
      if (int(bloatMap.data[i * bloatMap.info.width + j]) > 0)
      {
	//cout << "Data: " << int(map2d.data[i * map2d.info.width + j]) << endl;
      }
      if (int(bloatMap.data[i * bloatMap.info.width + j]) < 90)
      {
	double x = j * bloatMap.info.resolution + bloatMap.info.origin.position.x;
	double y = i * bloatMap.info.resolution + bloatMap.info.origin.position.y;
	
	cellVec = tf::Vector3(x - xObj, y - yObj, 0);
	
	if (cellVec.length() < minDistance && cellVec.angle(robotVec) <= DEG2RAD(30))
	{
	  minCell.setX(x);
	  minCell.setY(y);
	  minDistance = cellVec.length();
	}
      }
    }
  }
  
  cout << "Min Distance: " << minDistance << endl;
  
  cout << "Cell Relative: " << cellVec.getX() << ", " << cellVec.getY() << endl;
  
  cout << "Cell Vector: " << minCell.getX() << ", " << minCell.getY() << endl;
  
  double offset = 0.55;
  
  if (req.request.position.z > 0.1 && minDistance < 0.4)
  {
    res.recon_type = 3;
    offset = 0.6;
    ROS_INFO("Reachable, stamp environment");
  }
  else if (req.request.position.z > 0.1 && minDistance > 0.4)
  {
    res.recon_type = 4;
    offset = 1.0;
    ROS_INFO("Reachable, stairs environment");
  }
  else if (minDistance < 0.3)
  {
    res.recon_type = 1;
    ROS_INFO("Reachable, no reconfiguration required");
  }
  else if (minDistance < 0.7)
  {
    res.recon_type = 2;
    offset = 0.6;
    ROS_INFO("Reachable, tunnel environment");
  }
  else
  {
    res.recon_type = -1;
    ROS_INFO("Unreachable");
  }
  
  tf::Vector3 orient = objVec - minCell;
  double reconYaw = atan2(orient.getY(), orient.getX());
  q.setRPY(0, 0, reconYaw);
  
  double offDistance = 0;
  if (res.recon_type > 1)
  {
    offDistance = max(double(0.0), double(offset - minDistance));
  }
  
  cout << "offDistance: " << offDistance << endl;
  
  tf::Vector3 reconPoint = minCell - tf::Vector3(offDistance * cos(reconYaw), offDistance * sin(reconYaw), 0);
  
  cout << "Orientation: " << orient.getX() << ", " << orient.getY() << endl;
  cout << "Angular: " << reconYaw << endl;
  
  transform.setOrigin( tf::Vector3(minCell.getX(), minCell.getY(), 0.0) );
  transform.setRotation(q);
  
  tf::Transform transform2;
  transform2.setOrigin(tf::Vector3(-offDistance, 0.0, 0.0));
  q.setRPY(0, 0, 0);
  transform2.setRotation(q);
  
  geometry_msgs::Pose target;
  target.position.x = reconPoint.getX();
  target.position.y = reconPoint.getY();
  
  q.setRPY(0, 0, reconYaw);
  target.orientation.x = q.getX();
  target.orientation.y = q.getY();
  target.orientation.z = q.getZ();
  target.orientation.w = q.getW();
  
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "nav_point1"));
  br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "nav_point1", "target_point"));
  
  res.nav_point = target;
  
  return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "target_srv1");
  
  ros::NodeHandle node;

  ros::Rate rate(10.0);
  
  ros::ServiceServer service = node.advertiseService("get_target", target_req_cb);  
  
  tf::Transform modOffset;
  tf::Transform modTransform;
  
  ros::Subscriber grid_sub = node.subscribe("/map", 1, grid_cb);
  grid_pub = node.advertise<nav_msgs::OccupancyGrid>("/bloated_map", 1);
  
  cout << "Soooooo" << endl;
  
  ros::spin();  
  
  return 0;
}
