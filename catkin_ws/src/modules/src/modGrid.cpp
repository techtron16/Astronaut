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

bool mapReceived;
Octomap mapMsg;
double res = 0.01;
double rFactor = 1 / res;

void map_cb(const octomap_msgs::OctomapConstPtr& map)
{
  cout << ".";
  mapMsg = *map;
  mapReceived = true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "modGrid");
  
  ros::NodeHandle node;
  
  ros::Rate rate(10.0);
  
  tf::TransformListener listener;
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  tf::StampedTransform stransform;
  tf::Quaternion q;
  
  tf::Transform modOffset;
  tf::Transform modTransform;
  
  ros::Subscriber sub = node.subscribe("/octomap_binary", 15, map_cb);

  ros::Publisher path_pub = node.advertise<nav_msgs::Path>("/smorePath", 15);
  ros::Publisher grid_pub = node.advertise<nav_msgs::OccupancyGrid>("/nav_map", 15);
  
  cout << "Waiting for map" << endl;
  
  while (!mapReceived && ros::ok())
  {
    ros::spinOnce();
  }
  
  cout << "Got map" << endl;
  
  //if (!mapReceived) cout << "Never got map yiiiikess..." << endl;
  
  OcTree tree(*binaryMsgToMap(mapMsg));
  
  sleep(5);
  
  try{
    ros::Time gTime = ros::Time::now();
    listener.waitForTransform("map", "tag_0", gTime, ros::Duration(15.0));
    listener.lookupTransform("map", "tag_0", gTime, stransform);
  }
  catch (tf::TransformException &ex) {
    ROS_ERROR("%s",ex.what());
    ros::Duration(1.0).sleep();
  }
  point3d origin(stransform.getOrigin().x(), stransform.getOrigin().y(), stransform.getOrigin().z());
  
  cout << origin.x() << " : " << origin.y() << " : " << origin.z() << endl;
  
  try{
    ros::Time gTime = ros::Time::now();
    listener.waitForTransform("map", "goal", gTime, ros::Duration(15.0));
    listener.lookupTransform("map", "goal", gTime, stransform);
  }
  catch (tf::TransformException &ex) {
    ROS_ERROR("%s",ex.what());
    ros::Duration(1.0).sleep();
  }
  point3d goal(stransform.getOrigin().x(), stransform.getOrigin().y(), stransform.getOrigin().z());
  
  cout << "Reach Point: " << goal.x() << " : " << goal.y() << " : " << goal.z() << endl;
  
  try{
    ros::Time gTime = ros::Time::now();
    listener.waitForTransform("map", "dock", gTime, ros::Duration(15.0));
    listener.lookupTransform("map", "dock", gTime, stransform);
  }
  catch (tf::TransformException &ex) {
    ROS_ERROR("%s",ex.what());
    ros::Duration(1.0).sleep();
  }
  point3d dock(stransform.getOrigin().x(), stransform.getOrigin().y(), stransform.getOrigin().z());
  
  cout << "Docking Point: " << dock.x() << " : " << dock.y() << " : " << dock.z() << endl;
  
  double robotRad = 0.06;
  
  double minX, minY, minZ, maxX, maxY, maxZ;
  tree.getMetricMin(minX, minY, minZ);
  tree.getMetricMax(maxX, maxY, maxZ);
  point3d minPoint(minX, minY, minZ);
  point3d maxPoint(maxX, maxY, maxZ);
  
  cout << minX << ", " << maxX << ", " << minY << ", " << maxY << endl;
  minPoint = tree.keyToCoord(tree.coordToKey(minPoint));
  minX = minPoint.x();
  minY = minPoint.y();
  minZ = minPoint.z();
  maxPoint = tree.keyToCoord(tree.coordToKey(maxPoint));
  maxX = maxPoint.x();
  maxY = maxPoint.y();
  maxZ = maxPoint.z();
  
  cout << minX << ", " << maxX << ", " << minY << ", " << maxY << endl;
  
  tree.expand();
  
  int rangeX = round((maxX - minX) * rFactor);
  int rangeY = round((maxY - minY) * rFactor);
  
  vector<GridNode> gridMap(rangeX * rangeY, GridNode());
  vector<int> freeMap(rangeX * rangeY, 0);
  
  for (int x = 0; x < rangeX; x++)
  {
    for (int y = 0; y < rangeY; y++)
    {
      //cout << "XY: " << x << ", " << y << endl;
      gridMap[rangeX * y + x].coords = point3d(double(x) * res + minX, double(y) * res + minY, 0);
      
      for (int i = -1; i <= 1; i += 1)
      {
	for (int j = -1; j <= 1; j += 1)
	{
	  if ((i != 0 || j != 0) && x + i >= 0 && x + i < rangeX && y + j >= 0 && y + j < rangeY)
	  {
	    gridMap[rangeX * y + x].neighbors.push_back(&gridMap[rangeX * (y + j) + x + i]);
	    gridMap[rangeX * y + x].edges.push_back(sqrt(pow(i, 2) + pow(j, 2)) * res);
	    
	    //cout << gridMap[rangeX*y + x].neighbors.size() << ", " << gridMap[rangeX*y + x].edges.size() << endl;
	  }
	}
      }
    }
  }
  
  cout << "First" << endl;
  
  tree.expand();
  for (OcTree::leaf_iterator iter = tree.begin_leafs(); iter != tree.end_leafs(); iter++)
  {
    if (tree.isNodeOccupied(*iter) && iter.getZ() > 0.03 && iter.getCoordinate().distanceXY(origin) > 0.08)
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
    
    /*if (!tree.isNodeOccupied(*iter) && iter.getZ() > 0 && iter.getZ() <= 0.5)
    {
      int index = round((iter.getCoordinate().y() - minY) / res) * rangeX + round((iter.getCoordinate().x() - minX) / res);
      freeMap[index]++;
    }*/
  }
  
  /*for (int index = 0; index < rangeX * rangeY; index++)
  {
    if (freeMap[index] < 20 && gridMap[index].coords.distanceXY(firstPos) > 1 && gridMap[index].coords.distanceXY(origin) > 0.6)
    {
      gridMap[index].object = true;
      gridMap[index].occupied = true;
      
      for (double offX = -robotRad; offX <= robotRad; offX += res)
      {
	for (double offY = -robotRad; offY <= robotRad; offY += res)
	{
	  if (sqrt(pow(offX, 2) + pow(offY, 2)) <= robotRad)
	  {
	    int xInd = round((gridMap[index].coords.x() + offX - minX) * rFactor);
	    int yInd = round((gridMap[index].coords.y() + offY - minY) * rFactor);
	    
	    if (xInd >= 0 && xInd < rangeX && yInd >= 0 && yInd < rangeY)
	    {
	      int offIdx = yInd * rangeX + xInd;
	      if (gridMap[offIdx].coords.distanceXY(firstPos) > 0.4 && gridMap[offIdx].coords.distanceXY(origin) > 0.2)
	      {
		gridMap[offIdx].occupied = true;
	      }
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
      GridNode* nodePt = *iter;
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
  grid.header.frame_id = "map";
  
  nav_msgs::MapMetaData metas;
  metas.resolution = res;
  metas.origin.position.x = minX;
  metas.origin.position.y = minY;
  metas.origin.position.z = 0.01;
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
  path.header.frame_id = "map";
  
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
  pose.pose.position.x = dock.x();
  pose.pose.position.y = dock.y();
  pose.pose.position.z = 0.08;
  path.poses.push_back(pose);
  
  cout << "Path Message Generated" << endl;
  
  path_pub.publish<nav_msgs::Path>(path);
  ros::spinOnce();
  
  cout << "Path Message Published" << endl;
  
  return 0;
}