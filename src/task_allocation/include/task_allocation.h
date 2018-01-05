#ifndef TASK_ALLOCATION_H
#define TASK_ALLOCATION_H

#include <ros/ros.h>
#include <Core.hpp>
#include <behaviour.h>
#include <allocation_common/gazebo2world_info.h>
#include <allocation_common/robot2gazebo_info.h>
#include <allocation_common/terminal2robot_info.h>
#include <allocation_common/allocation2terminal_info.h>

class Task_Allocation
{
public:
    Task_Allocation(int argc, char **argv);
    ~Task_Allocation();
    void update_gazebo_world(const allocation_common::gazebo2world_info::ConstPtr & _msg);
    void update_terminal_info(const allocation_common::terminal2robot_info::ConstPtr & _msg);
    bool try2explore_();
    bool try2hit_();
    bool choose2hitOrexplore_();
    void loopControl(const ros::TimerEvent& event);
    void setVelCommond();
    void pubAllocation_info();
    void pauseAllocation();
    void stopAllocation();

public:
    Robot_info my_robot_;                          //my robot item
    std::vector<Robot_info> all_robots_;           //all robots
    std::vector<Task_info>  all_tasks_;            //all tasks
    std::vector<DPoint>     obstacles_;            //the obstacles in the field

    Behaviour* my_behaviour_;
    Terminal2Robots_info terminal_info_;           //the current terminal info for allocation

//    std::vector<Agent> init_agents_;             //record initial agent parameters
//    std::vector<Task>  init_tasks_;              //record initial task parameters

//    std::vector<int>   lab_agent_;               //record the number of agent that choose

    int num_task_valid_;                           //the number of task that uncompleted
    int num_target_valid_;                         //the number of target that had not been destroyed
    int num_robot_valid_;                          //the number of agent vaild

    float vel_x_;
    float vel_y_;
    float w_;

    bool is_world_update_;
    bool greedorprobability_;                      //greed 0, probability 1
    bool recordornot_;                             //not record 0, record 1
    bool powerordistance_;                         //power 0, distance 1

    ros::Subscriber  gazebo2world_sub_;
    ros::Subscriber  terminal2robot_sub_;
    ros::Publisher   robot2gazebo_pub_;
    ros::Publisher   allocation2terminal_pub_;
    ros::Timer       allocation_timer_;
    ros::NodeHandle* nh_;
};

#endif // TASK_ALLOCATION_H
