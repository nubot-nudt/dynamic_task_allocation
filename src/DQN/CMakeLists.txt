cmake_minimum_required(VERSION 2.8.3)
project(dqn_ros)

find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  message_generation
  roscpp
  rospy
  std_msgs
)

generate_messages(DEPENDENCIES std_msgs)

generate_dynamic_reconfigure_options(cfg/reward_cfg.cfg)

catkin_package(CATKIN_DEPENDS message_runtime)
