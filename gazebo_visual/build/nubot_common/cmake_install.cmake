# Install script for directory: /home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/nubot8/dynamic_allocation/gazebo_visual/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nubot_common/msgs" TYPE FILE FILES
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/Angle.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/Point2d.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/PPoint.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/Point3d.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/RobotInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/MotorInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/BallInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/BallInfo3d.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/ObstaclesInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/OminiVisionInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/currentCmd.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/VelCmd.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/OdoInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/CoachInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/PassCommands.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/WorldModelInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/StrategyInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/TargetInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/FrontBallInfo.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/simulation_strategy.msg"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/msgs/Pos2d.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nubot_common/srv" TYPE FILE FILES
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/srv/BallHandle.srv"
    "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/srv/Shoot.srv"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nubot_common/cmake" TYPE FILE FILES "/home/nubot8/dynamic_allocation/gazebo_visual/build/nubot_common/catkin_generated/installspace/nubot_common-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/nubot8/dynamic_allocation/gazebo_visual/devel/include/nubot_common")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/nubot8/dynamic_allocation/gazebo_visual/devel/share/roseus/ros/nubot_common")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/nubot8/dynamic_allocation/gazebo_visual/devel/share/common-lisp/ros/nubot_common")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/nubot8/dynamic_allocation/gazebo_visual/devel/share/gennodejs/ros/nubot_common")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/nubot8/dynamic_allocation/gazebo_visual/devel/lib/python2.7/dist-packages/nubot_common")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/nubot8/dynamic_allocation/gazebo_visual/devel/lib/python2.7/dist-packages/nubot_common")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/nubot8/dynamic_allocation/gazebo_visual/build/nubot_common/catkin_generated/installspace/nubot_common.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nubot_common/cmake" TYPE FILE FILES "/home/nubot8/dynamic_allocation/gazebo_visual/build/nubot_common/catkin_generated/installspace/nubot_common-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nubot_common/cmake" TYPE FILE FILES
    "/home/nubot8/dynamic_allocation/gazebo_visual/build/nubot_common/catkin_generated/installspace/nubot_commonConfig.cmake"
    "/home/nubot8/dynamic_allocation/gazebo_visual/build/nubot_common/catkin_generated/installspace/nubot_commonConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nubot_common" TYPE FILE FILES "/home/nubot8/dynamic_allocation/gazebo_visual/src/nubot_common/package.xml")
endif()

