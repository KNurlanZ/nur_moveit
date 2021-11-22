#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <geometry_msgs/Pose2D.h>

// Main moveit libraries are included
int main(int argc, char **argv)
{
 ros::init(argc, argv, "poser");
 ros::NodeHandle node_handle;
 ros::AsyncSpinner spinner(0);
 ros::Publisher pose_pub=node_handle.advertise<geometry_msgs::PoseStamped>("ppub", 1000);
 spinner.start(); // For moveit implementation we need AsyncSpinner, we cant use ros::spinOnce()
 static const std::string PLANNING_GROUP = "group1_j"; /* Now we specify with what group we want work,
 here group1 is the name of my group controller*/
 moveit::planning_interface::MoveGroupInterface
move_group(PLANNING_GROUP); // loading move_group
 const robot_state::JointModelGroup *joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP); //For joint control
 geometry_msgs::PoseStamped current_pose;
 geometry_msgs::PoseStamped data; // Pose in ROS is implemented using geometry_msgs::PoseStamped, google what is the type of this msg
 current_pose = move_group.getCurrentPose();
 data=current_pose;
 ros::Rate loop_rate(50); //Frequency
 while (ros::ok()){
     data=move_group.getCurrentPose();
     pose_pub.publish(data);
 }
 return 0;
}
