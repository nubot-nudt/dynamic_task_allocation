cmake_minimum_required(VERSION 2.8.3)
project(allocation_common)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set(CMAKE_BUILD_TYPE "Release")

find_package(catkin REQUIRED COMPONENTS
  message_filters
  message_generation
  roscpp
  rospy
  std_msgs
  std_srvs
)

add_message_files(DIRECTORY msgs FILES
    gazebo_robot_info.msg
    gazebo_task_info.msg
    allocation_robot_info.msg
    allocation_task_info.msg
    terminal2gazebo_info.msg
    terminal2robot_info.msg
    terminal2DQN_info.msg
    gazebo2world_info.msg
    robot2gazebo_info.msg
    allocation2terminal_info.msg
    Point2d.msg
    Pose.msg
    Twist.msg
    Observation.msg
    Teammateinfo.msg
    Taskinfo.msg)

add_service_files(DIRECTORY srv FILES
    GetAction.srv
    ReturnReward.srv)

generate_messages(DEPENDENCIES std_msgs)

set(allocation_common_includes ${catkin_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/include
)
include_directories(${allocation_common_includes})

catkin_package(
  INCLUDE_DIRS ${allocation_common_includes}
  INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
)
