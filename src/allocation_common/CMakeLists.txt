cmake_minimum_required(VERSION 2.8.3)
project(allocation_common)

set(CMAKE_BUILD_TYPE "Release")
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -pthread -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

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
    gazebo2world_info.msg
    robot2gazebo_info.msg
    allocation2terminal_info.msg
    Point2d.msg
    Pose.msg
    Twist.msg)

#add_service_files(DIRECTORY srv FILES)

generate_messages(DEPENDENCIES std_msgs)

set(allocation_common_includes ${catkin_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/include
)
include_directories(${allocation_common_includes})

catkin_package(
  INCLUDE_DIRS ${allocation_common_includes}
  INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
)
