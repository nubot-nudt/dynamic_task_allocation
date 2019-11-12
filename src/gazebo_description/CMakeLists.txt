cmake_minimum_required(VERSION 2.8.3)
cmake_policy(SET CMP0054 NEW)
project(gazebo_description)

find_package(catkin REQUIRED COMPONENTS 
  gazebo_ros  
)
find_package(gazebo REQUIRED)

catkin_package(
  CATKIN_DEPENDS 
    gazebo_ros 
  DEPENDS 
    GAZEBO
)

