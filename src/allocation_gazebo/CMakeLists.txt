cmake_minimum_required(VERSION 2.8.3)
cmake_policy(SET CMP0054 NEW)
project(allocation_gazebo)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_BUILD_TYPE "Release")

# Load catkin and all dependencies required for this package
find_package(catkin REQUIRED COMPONENTS 
  rospy
  roscpp
  std_msgs
  geometry_msgs
  sensor_msgs
  gazebo_ros  
  allocation_common
  dynamic_reconfigure
)

find_package(Protobuf REQUIRED)
find_package(gazebo REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# generate_dynamic_reconfigure_options(config/allocation_gazebo.cfg)

link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR}
                    ${catkin_INCLUDE_DIRS}
                    ${GAZEBO_INCLUDE_DIRS}
                    include)

catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS 
    sensor_msgs
    gazebo_ros 
    roscpp
    dynamic_reconfigure
  DEPENDS 
    GAZEBO
)				

#robot_gazebo
add_library(robot_gazebo src/robot_gazebo.cpp)
target_link_libraries(robot_gazebo ${catkin_LIBRARIES}
                                   ${GAZEBO_LIBRARIES}
                                   ${Boost_LIBRARIES}
                                   ${PROTOBUF_LIBRARIES}
                                   pthread)
#add_dependencies(robot_gazebo  ${PROJECT_NAME}_gencfg)
add_dependencies(robot_gazebo  ${catkin_EXPORTED_TARGETS})

#task_gazebo
add_library(task_gazebo src/task_gazebo.cpp)
target_link_libraries(task_gazebo ${catkin_LIBRARIES}
                                  ${GAZEBO_LIBRARIES}
                                  ${Boost_LIBRARIES}
                                  ${PROTOBUF_LIBRARIES}
                                  pthread)
#add_dependencies(task_gazebo  ${PROJECT_NAME}_gencfg)
add_dependencies(task_gazebo  ${catkin_EXPORTED_TARGETS})

#world_gazebo
add_library(world_gazebo src/world_gazebo.cpp)
target_link_libraries(world_gazebo ${catkin_LIBRARIES}
                                   ${GAZEBO_LIBRARIES}
                                   ${Boost_LIBRARIES}
                                   ${PROTOBUF_LIBRARIES}
                                   pthread)
#add_dependencies(world_gazebo  ${PROJECT_NAME}_gencfg)
add_dependencies(world_gazebo  ${catkin_EXPORTED_TARGETS})

