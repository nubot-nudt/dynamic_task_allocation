cmake_minimum_required(VERSION 2.8.3)
project(nubot_description)

find_package(catkin REQUIRED COMPONENTS 
  gazebo_ros  
)


catkin_package(
  CATKIN_DEPENDS 
    gazebo_ros 
  DEPENDS 
    gazebo
)

