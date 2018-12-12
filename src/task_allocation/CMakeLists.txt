cmake_minimum_required(VERSION 2.8.3)
project(task_allocation)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set(CMAKE_BUILD_TYPE "Release")

find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  message_generation
  dynamic_reconfigure
  roscpp
  rospy
  std_msgs
  std_srvs
  allocation_common
)

add_message_files(FILES
   DebugInfo.msg
 )

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS message_generation
                 dynamic_reconfigure
	         roscpp 
	         rospy  
		 std_msgs 
		 std_srvs 
		 DEPENDS
)

set(task_allocation_includes
               ${catkin_INCLUDE_DIRS}
               ${PROJECT_SOURCE_DIR}/include
)

include_directories(${task_allocation_includes})

add_executable(task_allocation_node src/main.cpp
                                    src/task_allocation.cpp
                                    src/behaviour.cpp
                                    src/subtargets.cpp
)

target_link_libraries(task_allocation_node
   ${catkin_LIBRARIES}
   ${Boost_LIBRARIES}
 )

add_executable(call_node src/call.cpp)
target_link_libraries(call_node ${catkin_LIBRARIES})
