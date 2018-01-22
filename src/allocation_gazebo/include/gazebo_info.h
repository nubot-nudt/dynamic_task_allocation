#ifndef GAZEBO_INFO_H
#define GAZEBO_INFO_H

/// \brief compile the code with Gazebo 8.0, there are many warning about "-Wdeprecated-declarations", ignored them
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <algorithm>
#include <assert.h>
#include <vector_angle.h>
#include <gazebo/gazebo.hh>
#include <gazebo/math/gzmath.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/Events.hh>
#include <sdf/sdf.hh>

#include <ros/callback_queue.h>
#include <ros/subscribe_options.h>
#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/ModelState.h>
#include <std_msgs/Float64MultiArray.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>

#include <allocation_common/gazebo2world_info.h>
#include <allocation_common/gazebo2terminal_info.h>
#include <allocation_common/gazebo_robot_info.h>
#include <allocation_common/gazebo_task_info.h>
#include <allocation_common/allocation_task_info.h>
#include <allocation_common/robot2gazebo_info.h>
#include <allocation_common/terminal2gazebo_info.h>
#include <dynamic_reconfigure/server.h>
#include <allocation_gazebo/Robot_GazeboConfig.h>
#include <Core.hpp>

#define PI 3.14159265
#define CM2M_CONVERSION 0.01
#define M2CM_CONVERSION 100

#define XUNIT_VECTOR math::Vector3::UnitX
#define YUNIT_VECTOR math::Vector3::UnitY
#define ZERO_VECTOR  math::Vector3::Zero
#define ZERO_QUATER  math::Quaternion(0,0,0,0)

const std::string robot_name="Robot";
const std::string task_name="Task";
const double g = 9.8;

// robot_state
struct Pose
{
    math::Vector3    position;
    math::Quaternion orient;
};

struct Twist
{
    math::Vector3    linear;
    math::Vector3    angular;
};

struct Robot_state
{
    std::string      robot_name;
    int              robot_ID;
    Pose             pose;
    Twist            twist;
    Robots_mode      current_mode;
    std::string      reference_frame;
};

// task_state
struct Task_state
{
    DPoint           world_pos;
    bool             istarget;
    bool             isvalid;
};

#endif //! GAZEBO_INFO_H
