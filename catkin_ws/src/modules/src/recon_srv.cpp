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
#include "modules/recon_req.h"

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

bool recon_req_cb(modules::recon_req::Request  &req, modules::recon_req::Response &resp)
{
  string egoTag = req.tags[0].data;
  string goalTag = req.tags[1].data;
  string face = req.tags[2].data;
  
  cout << egoTag << endl;
  
  ROS_INFO("request: %s, %s, %s", egoTag.c_str(), goalTag.c_str(), face.c_str());
  
  if (!egoTag.compare("tag_1"))
  {
    nav_msgs::Path path;
    path.header.stamp = ros::Time::now();
    path.header.frame_id = "base_link";
    
    geometry_msgs::PoseStamped pose;
    pose.header.stamp = path.header.stamp;
    pose.header.frame_id = path.header.frame_id;
    pose.pose.position.z = 0.08;
    
    pose.pose.position.x = 0.04;
    pose.pose.position.y = 0.06;
    path.poses.push_back(pose);
    pose.pose.position.x = 0.16;
    pose.pose.position.y = 0.06;
    path.poses.push_back(pose);
    pose.pose.position.x = 0.22;
    pose.pose.position.y = 0.0;
    path.poses.push_back(pose);
    pose.pose.position.x = 0.14;
    pose.pose.position.y = 0.0;
    path.poses.push_back(pose);
    pose.pose.position.x = 0.09;
    pose.pose.position.y = 0.0;
    path.poses.push_back(pose);
  
    path_pub.publish<nav_msgs::Path>(path);
    ros::spinOnce();

    ROS_INFO("Path Published Early");
    
    resp.path = path;

    return true;
  }
  else if (!egoTag.compare("tag_2"))
  { 
    nav_msgs::Path path;
    path.header.stamp = ros::Time::now();
    path.header.frame_id = "base_link";
    
    geometry_msgs::PoseStamped pose;
    pose.header.stamp = path.header.stamp;
    pose.header.frame_id = path.header.frame_id;
    pose.pose.position.z = 0.08;
    
    pose.pose.position.x = 0.04;
    pose.pose.position.y = -0.1;
    path.poses.push_back(pose);
    pose.pose.position.x = 0.22;
    pose.pose.position.y = -0.1;
    path.poses.push_back(pose);
    pose.pose.position.x = 0.32;
    pose.pose.position.y = 0.0;
    path.poses.push_back(pose);
    pose.pose.position.x = 0.22;
    pose.pose.position.y = 0.0;
    path.poses.push_back(pose);
    pose.pose.position.x = 0.17;
    pose.pose.position.y = 0.0;
    path.poses.push_back(pose);
    
    path_pub.publish<nav_msgs::Path>(path);
    ros::spinOnce();
    
    ROS_INFO("Path Published Early");
    
    resp.path = path;

    return true;
  }
  
  tf::TransformListener listener;
  tf::StampedTransform stransform;
  
  tf::TransformBroadcaster br;
  
  tf::Transform modOffset;
  tf::Transform modOffset1;
  tf::Transform modOffset2;
  
  point3d origin;
  point3d goal;
  point3d goal1;
  point3d goal2;
  
  q.setRPY(0, 0, 0);
  modOffset.setRotation(q);
  modOffset.setOrigin( tf::Vector3(0.2,0.0, 0.0) );

  q.setRPY(0, 0, 0);
  modOffset1.setRotation(q);
  modOffset1.setOrigin( tf::Vector3(0.1,0.0, 0.0) );

  q.setRPY(0, 0, 0);
  modOffset2.setRotation(q);
  modOffset2.setOrigin( tf::Vector3(0.05,0.0, 0.0) );
  
  while (ros::ok())
  {
    try{
      ros::Time gTime = ros::Time::now();
      listener.waitForTransform("base_link", egoTag, gTime, ros::Duration(5.0));
      listener.lookupTransform("base_link", egoTag, gTime, stransform);
      
      origin = point3d(stransform.getOrigin().x(), stransform.getOrigin().y(), stransform.getOrigin().z());
      cout << origin.x() << " : " << origin.y() << " : " << origin.z() << endl;
      break;
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      continue;
    }
  }
  
  while (ros::ok())
  {
    br.sendTransform(tf::StampedTransform(modOffset, ros::Time::now(), goalTag, "goal"));
    try{
      ros::Time gTime = ros::Time::now() - ros::Duration(0.1);
      listener.waitForTransform("base_link", "goal", gTime, ros::Duration(5.0));
      listener.lookupTransform("base_link", "goal", gTime, stransform);
      
      goal = point3d(stransform.getOrigin().x(), stransform.getOrigin().y(), stransform.getOrigin().z());
      break;
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      continue;
    }
  }
  
  while (ros::ok())
  {
    br.sendTransform(tf::StampedTransform(modOffset1, ros::Time::now(), goalTag, "goal1"));
    try{
      ros::Time gTime = ros::Time::now() - ros::Duration(0.1);
      listener.waitForTransform("base_link", "goal1", gTime, ros::Duration(5.0));
      listener.lookupTransform("base_link", "goal1", gTime, stransform);
      
      goal1 = point3d(stransform.getOrigin().x(), stransform.getOrigin().y(), stransform.getOrigin().z());
      break;
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      continue;
    }
  }
  
  while (ros::ok())
  {
    br.sendTransform(tf::StampedTransform(modOffset2, ros::Time::now(), goalTag, "goal2"));
    try{
      ros::Time gTime = ros::Time::now() - ros::Duration(0.1);
      listener.waitForTransform("base_link", "goal2", gTime, ros::Duration(5.0));
      listener.lookupTransform("base_link", "goal2", gTime, stransform);
      
      goal2 = point3d(stransform.getOrigin().x(), stransform.getOrigin().y(), stransform.getOrigin().z());
      break;
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      continue;
    }
  }
  
  double robotRad = 0.03;
  
  double minX = -1.0;
  double maxX = 1.0;
  double minY = -1.0;
  double maxY = 1.0;
  
  cout << minX << ", " << maxX << ", " << minY << ", " << maxY << endl;
  
  int rangeX = round((maxX - minX) * rFactor);
  int rangeY = round((maxY - minY) * rFactor);
  
  vector<GridNode> gridMap(rangeX * rangeY, GridNode());
  vector<int> freeMap(rangeX * rangeY, 0);
  
  for (int x = 0; x < rangeX; x++)
  {
    for (int y = 0; y < rangeY; y++)
    {
      gridMap[rangeX * y + x].coords = point3d(double(x) * res + minX, double(y) * res + minY, 0);
      
      for (int i = -1; i <= 1; i += 1)
      {
	for (int j = -1; j <= 1; j += 1)
	{
	  if ((i != 0 || j != 0) && x + i >= 0 && x + i < rangeX && y + j >= 0 && y + j < rangeY)
	  {
	    gridMap[rangeX * y + x].neighbors.push_back(&gridMap[rangeX * (y + j) + x + i]);
	    gridMap[rangeX * y + x].edges.push_back(sqrt(pow(i, 2) + pow(j, 2)) * res);
	  }
	}
      }
    }
  }
  
  cout << "First" << endl;
  
  /*for (vector<apriltags_ros::AprilTagDetection>::iterator iter = tagPoses.detections.begin(); iter != tagPoses.detections.end(); iter++)
  {
    apriltags_ros::AprilTagDetection tag = *iter;
    
    int index = int((tag.pose.pose.position.y - minY) / res) * rangeX + (tag.pose.pose.position.x - minX) / res;
      
    gridMap[index].object = true;
    gridMap[index].occupied = true;
    
    for (double offX = -robotRad; offX <= robotRad; offX += res)
    {
      for (double offY = -robotRad; offY <= robotRad; offY += res)
      {
	if (sqrt(pow(offX, 2) + pow(offY, 2)) <= 2 * robotRad)
	{
	  int xInd = (gridMap[index].coords.x() + offX - minX) * rFactor;
	  int yInd = (gridMap[index].coords.y() + offY - minY) * rFactor;
	  
	  if (xInd >= 0 && xInd < rangeX && yInd >= 0 && yInd < rangeY)
	  {
	    int offIdx = yInd * rangeX + xInd;
	    gridMap[offIdx].occupied = true;
	  }
	}
      }
    }
  }*/
  
  /*tree->expand();
  for (OcTree::leaf_iterator iter = tree->begin_leafs(); iter != tree->end_leafs(); iter++)
  {
    if (tree->isNodeOccupied(*iter) && iter.getZ() > 0.05 && iter.getCoordinate().distanceXY(origin) > 0.08)
    {
      int index = int((iter.getCoordinate().y() - minY) / res) * rangeX + (iter.getCoordinate().x() - minX) / res;
      
      gridMap[index].object = true;
      gridMap[index].occupied = true;
      
      for (double offX = -robotRad; offX <= robotRad; offX += res)
      {
    for (double offY = -robotRad; offY <= robotRad; offY += res)
    {
      if (sqrt(pow(offX, 2) + pow(offY, 2)) <= robotRad)
      {
        int xInd = (gridMap[index].coords.x() + offX - minX) * rFactor;
        int yInd = (gridMap[index].coords.y() + offY - minY) * rFactor;
        
        if (xInd >= 0 && xInd < rangeX && yInd >= 0 && yInd < rangeY)
        {
          int offIdx = yInd * rangeX + xInd;
          gridMap[offIdx].occupied = true;
        }
      }
    }
      }
    }
  }*/
  
  cout << "Second" << endl;
  
  cout << rangeX << ", " << rangeY << " : " << int((origin.x() - minX) * rFactor) << ", " << int((origin.y() - minY) * rFactor) << endl;
  
  int origIdx = rangeX * int((origin.y() - minY) / res) + int((origin.x() - minX) / res);
  
  cout << origIdx << "     " << gridMap.size() << endl;
  
  GridNode* originNode = &gridMap[origIdx];
  originNode->cost = 0;
  
  cout << "Orig Node: " << originNode->coords.x() << ", " << originNode->coords.y() << endl;
  
  cout << "Got Here" << endl;
  
  MinHeap heapy;
  
  heapy.Push(originNode);
  
  cout << "And Here" << endl;
  
  while (heapy.GetLength() > 0)
  {
    GridNode* minNode = heapy.Pop();
    
    vector<float>::iterator edgeIt = minNode->edges.begin();
    for (vector<GridNode*>::iterator iter = minNode->neighbors.begin(); iter != minNode->neighbors.end(); iter++, edgeIt++)
    {
      //GridNode* nodePt = *iter; // unused?
      if ((*iter)->occupied == 0 && (*iter)->cost > (minNode->cost + *edgeIt))
      {
    (*iter)->parent = minNode;
    
    if ((*iter)->state == 0)
    {
      (*iter)->cost = minNode->cost + *edgeIt;
      heapy.Push((*iter));
      (*iter)->state = 1;
    }
    else if ((*iter)->state == 1)
    {
      heapy.Update((*iter)->heapIdx, minNode->cost + *edgeIt);
    }
      }
    }
  }
  
  cout << "Dijkstra Path Complete" << endl;
  
  nav_msgs::OccupancyGrid grid;
  grid.header.stamp = ros::Time::now();
  grid.header.frame_id = "base_link";
  
  nav_msgs::MapMetaData metas;
  metas.resolution = res;
  metas.origin.position.x = minX;
  metas.origin.position.y = minY;
  metas.origin.position.z = 0.0;
  metas.height = rangeY;
  metas.width = rangeX;
  
  grid.info = metas;
  
  cout << gridMap.size() << endl;
  
  for (vector<GridNode>::iterator iter = gridMap.begin(); iter != gridMap.end(); iter++)
  {    
    if (iter->occupied)
    {
      grid.data.push_back(100);
    }
    else
    {
      grid.data.push_back(0);
    }
  }
  
  grid_pub.publish(grid);
  
  cout << "Map Published" << endl;
  
  GridNode* endNode = &gridMap[rangeX * int((goal.y() - minY) / res) + int((goal.x() - minX) / res)];
  
  cout << "End Node: " << endNode->coords.x() << ", " << endNode->coords.y() << endl;
  
  vector<point3d> waypoints;
  
  while (endNode != NULL)
  {
    //cout << endNode->coords.x() << ", " << endNode->coords.y() << endl;
    //cout << "Cost: " << endNode->cost << endl;
    endNode->cost = 0;
    waypoints.push_back(endNode->coords);
    //cout << endNode->coords.x() << ", " << endNode->coords.y() << endl;
    endNode = endNode->parent;
  }
  
  reverse(waypoints.begin(), waypoints.end());
  
  nav_msgs::Path path;
  path.header.stamp = ros::Time::now();
  path.header.frame_id = "base_link";
  
  int state = 0;
  int oldState = -1;
  for (vector<point3d>::iterator iter = waypoints.begin(); iter != waypoints.end(); iter++)
  {
    geometry_msgs::PoseStamped pose;
    pose.header.stamp = path.header.stamp;
    pose.header.frame_id = path.header.frame_id;
    pose.pose.position.x = iter->x();
    pose.pose.position.y = iter->y();
    pose.pose.position.z = 0.08;
    
    if (path.poses.size() > 0)
    {
      if (iter->x() == path.poses.back().pose.position.x)
      {
    state = 0;
      }
      else if (iter->y() == path.poses.back().pose.position.y)
      {
    state = 1;
      }
      else
      {
    state = 2;
      }
    }
    
    cout << "State, Old State, Size: " << state << " : " << oldState << " : " << path.poses.size() << endl;
    
    if (path.poses.size() > 1 && state == oldState)
    {
      path.poses.pop_back();
      cout << pose.pose.position.x << ", " << pose.pose.position.y << endl;
    }
    
    path.poses.push_back(pose);
    
    oldState = state;
  }

  geometry_msgs::PoseStamped pose;
  pose.header.stamp = path.header.stamp;
  pose.header.frame_id = path.header.frame_id;
  pose.pose.position.x = goal1.x();
  pose.pose.position.y = goal1.y();
  pose.pose.position.z = 0.08;
  path.poses.push_back(pose);

  pose.header.stamp = path.header.stamp;
  pose.header.frame_id = path.header.frame_id;
  pose.pose.position.x = goal2.x();
  pose.pose.position.y = goal2.y();
  pose.pose.position.z = 0.08;
  path.poses.push_back(pose);
  
  cout << "Path Message Generated" << endl;
  
  path_pub.publish<nav_msgs::Path>(path);
  ros::spinOnce();
  
  cout << "Path Message Published" << endl;
  
  resp.path = path;
  
  /*while (ros::ok())
  {
    path_pub.publish<nav_msgs::Path>(path);
    grid_pub.publish(grid);
    
    br.sendTransform(tf::StampedTransform(modOffset, ros::Time::now(), goalTag, "goal"));
    br.sendTransform(tf::StampedTransform(modOffset1, ros::Time::now(), goalTag, "goal1"));
    br.sendTransform(tf::StampedTransform(modOffset2, ros::Time::now(), goalTag, "goal2"));
    ros::spinOnce();
  }*/
  
  return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "target_srv");
  
  ros::NodeHandle node;

  ros::Rate rate(10.0);
  
  ros::ServiceServer service = node.advertiseService("recon_path", recon_req_cb);
  
  path_pub = node.advertise<nav_msgs::Path>("/smorePath", 15);
  grid_pub = node.advertise<nav_msgs::OccupancyGrid>("/nav_map", 15);  

  ros::spin();  
  
  return 0;
}