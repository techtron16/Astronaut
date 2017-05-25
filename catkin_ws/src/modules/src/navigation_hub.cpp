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

//apriltags_ros::AprilTagDetectionArray tagPoses;

ros::Publisher path_pub;
ros::Publisher grid_pub;

void generatePath(string egoTag, string goalTag);

void blob_cb(const geometry_msgs::Vector3ConstPtr& msg)
{
  pinkReceived = true;
}

void nbv_cb(const std_msgs::Float64MultiArrayConstPtr& nbv)
{
  ROS_INFO("Navigation Hub has received NBV");
  
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();  
  goal.target_pose.pose.position.x = double(nbv->data[0]);
  goal.target_pose.pose.position.y = double(nbv->data[1]);
  
  q.setRPY(0, 0, nbv->data[3]);
  goal.target_pose.pose.orientation.x = double(q.x());
  goal.target_pose.pose.orientation.y = double(q.y());
  goal.target_pose.pose.orientation.z = double(q.z());
  goal.target_pose.pose.orientation.w = double(q.w());
  
  nbvReceived = true;
}

void grid_cb(const nav_msgs::OccupancyGridConstPtr& grid)
{
  map2d = *grid;
  gridReceived = true;
  //cout << "Got emmm" << endl;
}

string parse(string input, int id)
// String parsing function to extract data:
{
    // 0 = egoTagString, 1 = ego face, 2 = dockTagString, 3 = dock face
    std::string s = input;
    std::string delimiter = ":";

    size_t pos = 0;
    std::string token;
    int count = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if (count == id) {
            return token;
        }
        s.erase(0, pos + delimiter.length());
        count++;
    }
    return s;
}

/*void tags_cb(apriltags_ros::AprilTagDetectionArrayConstPtr& tags)
{
  tagPoses = *tags;
}*/

void tag_info_cb(std_msgs::String dataString)
// Callback for tag information topic
{
  string egoTag = parse(dataString.data, 0);
  string goalTag = parse(dataString.data, 2);
  ROS_INFO("Received Reconfig Request");
  cout << "Tags: " << egoTag << " : " << goalTag << endl;
  generatePath(egoTag, goalTag);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "nav_hub");
  
  ros::NodeHandle node;

  ros::Rate rate(10.0);
  
  MoveBaseClient ac("move_base", true);
  
  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  tf::TransformListener listener;
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  tf::StampedTransform stransform;
  tf::Quaternion q;
  
  tf::Transform modOffset;
  tf::Transform modTransform;
  
  ros::Subscriber sub = node.subscribe("/nbv", 15, nbv_cb);
  ros::Subscriber blob_sub = node.subscribe("/blobPt", 15, blob_cb);
  ros::Subscriber grid_sub = node.subscribe("/map", 1, grid_cb);

  ros::Publisher nbv_pub = node.advertise<std_msgs::Int32>("/nbv_iter", 15);
  ros::Publisher recon_pub = node.advertise<std_msgs::Int32>("/config_state", 15);
  ros::Publisher cancel_pub = node.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 15);
  ros::Publisher stop_pub = node.advertise<geometry_msgs::Twist>("/navigation_velocity_smoother/raw_cmd_vel", 15);
  
  path_pub = node.advertise<nav_msgs::Path>("/smorePath", 15);
  grid_pub = node.advertise<nav_msgs::OccupancyGrid>("/nav_map", 15);
  
  ros::Subscriber tagInfoSub = node.subscribe("/reconf_request", 10, tag_info_cb);
  
  //ros::Subscriber tag_sub = node.subscribe("/tag_detections", 10, tags_cb);
  
  bool pinkSeen = false;
  double maxReach = 0.7;
  double carReach = 0.06;
  
  //int wait;
  //cin >> wait;
  
  while (ros::ok())
  {
    std_msgs::Int32 temp;
    temp.data = 2;
    nbv_pub.publish<std_msgs::Int32>(temp);
    cout << "Publishhhhh" << endl;
    ros::spinOnce();
    
    ROS_INFO("Publishing NBV Request");
    ROS_INFO("Waiting for a target (to destroy)");
    
    while (!nbvReceived && ros::ok())
    {
      ros::spinOnce();
    }
    
    cout << "Goal: " << goal.target_pose.pose.position.x << " , " << goal.target_pose.pose.position.y << endl;
    
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
    nbvReceived = false;
    
    double xObj, yObj;
    tf::Vector3 objVec(0, 0, 0);
    
    while ((ac.getState() == actionlib::SimpleClientGoalState::PENDING || ac.getState() == actionlib::SimpleClientGoalState::ACTIVE) && ros::ok())
    {
      ros::spinOnce();
      
      if (pinkReceived)
      {
	ROS_INFO("Saw pink...");
	
	try{
	  ros::Time gTime = ros::Time::now() - ros::Duration(0.5);
	  listener.waitForTransform("map", "colorObj", gTime, ros::Duration(5));
	  listener.lookupTransform("map", "colorObj", gTime, stransform);
	}
	catch (tf::TransformException &ex) {
	  ROS_ERROR("%s",ex.what());
	  pinkReceived = false;
	  continue;
	}
	
	xObj = stransform.getOrigin().getX();
	yObj = stransform.getOrigin().getY();
	
	objVec = tf::Vector3(xObj, yObj, 0);
	
	try{
	  ros::Time gTime = ros::Time::now();
	  listener.waitForTransform("map", "base_footprint", gTime, ros::Duration(5));
	  listener.lookupTransform("map", "base_footprint", gTime, stransform);
	}
	catch (tf::TransformException &ex) {
	  ROS_ERROR("%s",ex.what());
	  pinkReceived = false;
	  continue;
	}
	
	ROS_INFO("Registered Pink");
	
	actionlib_msgs::GoalID stopMsg;
	cancel_pub.publish(stopMsg);
	
	geometry_msgs::Twist twist;
	twist.linear.x = 0;
	twist.linear.y = 0;
	twist.linear.z = 0;
	twist.angular.x = 0;
	twist.angular.y = 0;
	twist.angular.z = 0;
	
	for (int i = 1; i < 50; i++)
	{
	  stop_pub.publish(twist);
	  ros::Duration(0.1).sleep();
	}
	
	ROS_INFO("Map Should be Updated Now");
	
	break;
      }
    }
    
    if (pinkReceived)
    {
      //--------------
      //Bloat Map
      //--------------
      
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
      
      //grid_pub.publish(bloatMap);
      
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
	  if (int(bloatMap.data[i * bloatMap.info.width + j]) < 99)
	  {
	    double x = j * bloatMap.info.resolution + bloatMap.info.origin.position.x;
	    double y = i * bloatMap.info.resolution + bloatMap.info.origin.position.y;
	    
	    cellVec = tf::Vector3(x - xObj, y - yObj, 0);
	    
	    if (cellVec.length() < minDistance && cellVec.angle(robotVec) <= DEG2RAD(20))
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
      
      std_msgs::Int32 config;
      
      if (minDistance < 0.2)
      {
	config.data = 1;
	ROS_INFO("Reachable, no reconfiguration required");
      }
      else if (minDistance < 0.5)
      {
	config.data = 2;
	ROS_INFO("Reachable, reconfigure to proboscis to proceed");
      }
      else
      {
	config.data = -1;
	ROS_INFO("Unreachable");
      }
      
      tf::Vector3 orient = objVec - minCell;
      double reconYaw = atan2(orient.getY(), orient.getX());
      q.setRPY(0, 0, reconYaw);
      
      double offDistance = max(double(0.0), double(0.4 - minDistance));
      
      tf::Vector3 reconPoint = minCell - tf::Vector3(offDistance * cos(reconYaw), offDistance * sin(reconYaw), 0);
      
      cout << "Orientation: " << orient.getX() << ", " << orient.getY() << endl;
      cout << "Angular: " << reconYaw << endl;
      
      transform.setOrigin( tf::Vector3(minCell.getX(), minCell.getY(), 0.0) );
      transform.setRotation(q);
      
      tf::Transform transform2;
      transform2.setOrigin(tf::Vector3(-offDistance, 0.0, 0.0));
      q.setRPY(0, 0, 0);
      transform2.setRotation(q);
      
      goal.target_pose.header.frame_id = "map";
      goal.target_pose.header.stamp = ros::Time::now();  
      goal.target_pose.pose.position.x = reconPoint.getX();
      goal.target_pose.pose.position.y = reconPoint.getY();
      
      q.setRPY(0, 0, reconYaw);
      goal.target_pose.pose.orientation.x = q.getX();
      goal.target_pose.pose.orientation.y = q.getY();
      goal.target_pose.pose.orientation.z = q.getZ();
      goal.target_pose.pose.orientation.w = q.getW();
      
      br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "nav_point1"));
      br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "nav_point1", "nav_point2"));
      
      ROS_INFO("Sending goal");
      ac.sendGoal(goal);
      
      /*while ((ac.getState() == actionlib::SimpleClientGoalState::PENDING || ac.getState() == actionlib::SimpleClientGoalState::ACTIVE) && ros::ok())
      {
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "nav_point1"));
	try{
	  ros::Time gTime = ros::Time::now() - ros::Duration(0.5);
	  listener.waitForTransform("colorObj", "nav_point1", gTime, ros::Duration(5));
	  listener.lookupTransform("colorObj", "nav_point1", gTime, stransform);
	  transform.setOrigin(stransform.getOrigin());
	  transform.setRotation(stransform.getRotation());
	  break;
	}
	catch (tf::TransformException &ex) {
	  ROS_ERROR("%s",ex.what());
	  continue;
	}
	
	rate.sleep();
      }*/
      
      while ((ac.getState() == actionlib::SimpleClientGoalState::PENDING || ac.getState() == actionlib::SimpleClientGoalState::ACTIVE) && ros::ok())
      {
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "nav_point1"));
	br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "nav_point1", "nav_point2"));
	
	/*try{
	  ros::Time gTime = ros::Time::now() - ros::Duration(0.5);
	  listener.waitForTransform("map", "nav_point2", gTime, ros::Duration(5));
	  listener.lookupTransform("map", "nav_point2", gTime, stransform);
	}
	catch (tf::TransformException &ex) {
	  ROS_ERROR("%s",ex.what());
	  continue;
	}
	
	goal.target_pose.pose.position.x = stransform.getOrigin().getX();
	goal.target_pose.pose.position.y = stransform.getOrigin().getY();
	
	goal.target_pose.pose.orientation.x = stransform.getRotation().getX();
	goal.target_pose.pose.orientation.y = stransform.getRotation().getY();
	goal.target_pose.pose.orientation.z = stransform.getRotation().getZ();
	goal.target_pose.pose.orientation.w = stransform.getRotation().getW();
	
	ROS_INFO("Sending goal");
	ac.sendGoal(goal);
	
	ros::Duration(3).sleep();*/
	
	rate.sleep();
      }
      
      ROS_INFO("WAITING TO CORRECT ORIENTATION");
      
      geometry_msgs::Twist twist;
      twist.linear.x = 0;
      twist.linear.y = 0;
      twist.linear.z = 0;
      twist.angular.x = 0;
      twist.angular.y = 0;
      twist.angular.z = 0;
      
      for (int i = 1; i < 50; i++)
      {
	stop_pub.publish(twist);
	ros::Duration(0.1).sleep();
      }
      
      /*try{
	ros::Time gTime = ros::Time::now() - ros::Duration(0.5);
	listener.waitForTransform("map", "colorObj", gTime, ros::Duration(5));
	listener.lookupTransform("map", "colorObj", gTime, stransform);
	
	objVec = stransform.getOrigin();
      }
      catch (tf::TransformException &ex) {
	ROS_ERROR("%s",ex.what());
      }*/
      
      while (ros::ok())
      {
	try{
	  ros::Time gTime = ros::Time::now();
	  listener.waitForTransform("map", "base_footprint", gTime, ros::Duration(5));
	  listener.lookupTransform("map", "base_footprint", gTime, stransform);
	  robotVec = stransform.getOrigin();
	  break;
	}
	catch (tf::TransformException &ex) {
	  ROS_ERROR("%s",ex.what());
	  continue;
	}
      }
      
      orient = objVec - robotVec;
      reconYaw = atan2(orient.getY(), orient.getX());
      
      goal.target_pose.header.frame_id = "map";
      goal.target_pose.header.stamp = ros::Time::now();  
      goal.target_pose.pose.position.x = robotVec.getX();
      goal.target_pose.pose.position.y = robotVec.getY();
      
      q.setRPY(0, 0, reconYaw);
      goal.target_pose.pose.orientation.x = q.getX();
      goal.target_pose.pose.orientation.y = q.getY();
      goal.target_pose.pose.orientation.z = q.getZ();
      goal.target_pose.pose.orientation.w = q.getW();
      
      ac.sendGoal(goal);
      
      while ((ac.getState() == actionlib::SimpleClientGoalState::PENDING || ac.getState() == actionlib::SimpleClientGoalState::ACTIVE) && ros::ok())
      {
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "nav_point1"));
	br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "nav_point1", "nav_point2"));
      }
      
      ROS_INFO("Fire up Apriltags");
      
      twist.linear.x = 0;
      twist.linear.y = 0;
      twist.linear.z = 0;
      twist.angular.x = 0;
      twist.angular.y = 0;
      twist.angular.z = 0;
      
      for (int i = 1; i < 50; i++)
      {
	stop_pub.publish(twist);
	ros::Duration(0.1).sleep();
      }
      
      int tempy;
      cin >> tempy;
	
      ROS_INFO("Starting Recon");
      
      recon_pub.publish<std_msgs::Int32>(config);
      
      while (ros::ok())
      {
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "nav_point1"));
	br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "nav_point1", "nav_point2"));
	rate.sleep();
      }
      
      return 0;
    }
    else
    {
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
	ROS_INFO("Hooray, the base moved 1 meter forward");
      }
      else
      {
	ROS_INFO("The base failed to move forward 1 meter for some reason");
      }
    }    
  }
  
  return 0;
}

void generatePath(string egoTag, string goalTag)
{
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

    return;
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

    return;
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
  
  /*while (ros::ok())
  {
    path_pub.publish<nav_msgs::Path>(path);
    grid_pub.publish(grid);
    
    br.sendTransform(tf::StampedTransform(modOffset, ros::Time::now(), goalTag, "goal"));
    br.sendTransform(tf::StampedTransform(modOffset1, ros::Time::now(), goalTag, "goal1"));
    br.sendTransform(tf::StampedTransform(modOffset2, ros::Time::now(), goalTag, "goal2"));
    ros::spinOnce();
  }*/
}
