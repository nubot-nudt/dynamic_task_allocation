cmake_minimum_required(VERSION 2.8.3)
project(common)

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
                  terminal2gazebo_info.msg)

#add_service_files(DIRECTORY srv FILES)

generate_messages(DEPENDENCIES std_msgs)

set(common_includes ${catkin_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/include
)
include_directories(${common_includes})

catkin_package(
  INCLUDE_DIRS ${common_includes}
  INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
)
