cmake_minimum_required(VERSION 2.8.3)
project(world_model)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set(CMAKE_BUILD_TYPE "Release")

find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  common
  dynamic_reconfigure
  message_filters
  message_generation
  roscpp
  rospy
  std_msgs
  std_srvs
)

find_package(Eigen REQUIRED)
find_package(Boost REQUIRED)
find_package(Qt5Widgets)
find_package(Threads)

set(world_model_includes
               include
               ${catkin_INCLUDE_DIRS}
               ${Boost_INCLUDE_DIRS}
               ${EIGEN_INCLUDE_DIRS}
)

include_directories(${world_model_includes})

add_library(world_model  STATIC
                         src/agent.cpp
                         src/task.cpp
)

target_link_libraries(world_model ${catkin_LIBRARIES})

catkin_package(
  INCLUDE_DIRS   include
  CATKIN_DEPENDS dynamic_reconfigure
                 message_filters 
                 message_generation  
                 roscpp rospy  
                 std_msgs 
                 std_srvs
  LIBRARIES      world_model
)

add_executable(world_model_node
               src/main.cpp
               src/world_model.cpp
)
target_link_libraries(world_model_node
    ${catkin_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    world_model
)
qt5_use_modules(world_model_node Widgets)
qt5_use_modules(world_model Widgets)
