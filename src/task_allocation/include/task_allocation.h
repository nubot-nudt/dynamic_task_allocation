#ifndef TASK_ALLOCATION_H
#define TASK_ALLOCATION_H

#include <ros/ros.h>
#include <Core.hpp>
#include <behaviour.h>
#include <allocation_common/gazebo2world_info.h>
#include <allocation_common/robot2gazebo_info.h>
#include <allocation_common/terminal2robot_info.h>
#include <allocation_common/allocation2terminal_info.h>
#include <allocation_common/GetAction.h>
#include <allocation_common/ReturnReward.h>
#include <geometry_msgs/Point.h>
#include <dynamic_reconfigure/server.h>
#include <dqn_ros/reward_cfgConfig.h>

class Task_Allocation
{
public:
    Task_Allocation(int argc, char **argv);
    ~Task_Allocation();
    void update_gazebo_world(const allocation_common::gazebo2world_info::ConstPtr & _msg);
    void update_terminal_info(const allocation_common::terminal2robot_info::ConstPtr & _msg);    
    void loopControl(const ros::TimerEvent& event);
    void setVelCommond();
    void pubAllocation_info();
    void pubDrawing_info();
    void pauseAllocation();
    void stopAllocation();
    void ParamChanged(dqn_ros::reward_cfgConfig &config, uint32_t level);

    //for predition method
    bool try2explore_();
    bool try2hit_();
    bool choose2hitOrexplore_();
    //for market-base method
    bool which2hit_();
    bool which2explore_();
    //for DQN method
    bool choose_task_();
    bool return_rewrad_(char causes, DPoint task_pos=DPoint(0,0));
public:
    Robot_info my_robot_;                          //my robot item
    std::vector<Robot_info> all_robots_;           //all robots
    std::vector<Task_info>  all_tasks_;            //all tasks
    std::vector<DPoint>     obstacles_;            //the obstacles in the field

    Behaviour* my_behaviour_;
    Terminal2Robots_info terminal_info_;           //the current terminal info for allocation

    int num_task_valid_;                           //for prediction and market_base: the number of task that uncompleted
    int num_target_valid_;                         //for prediction and market_base: the number of target that had not been destroyed
    int num_task_unallocated_;                     //only for market_base: the number of task that unallocated
    int num_target_unallocated_;                   //only for market_base: the number of target that unallocated

    bool is_world_update_;
    bool bid_new_task_;
    bool bid_new_target_;
    bool is_target_completed;
    bool is_task_explored;
    bool is_target_dropped;
    bool is_task_dropped;
    bool is_all_completed;
    DPoint start_point_;

    float Reward_I;                                 //the parameters of the dqn reward
    float Reward_D;
    float Reward_C;
    float Reward_E;
    float Reward_R;

private:
    dynamic_reconfigure::Server<dqn_ros::reward_cfgConfig> server;
    dynamic_reconfigure::Server<dqn_ros::reward_cfgConfig>::CallbackType f;

    ros::ServiceClient get_action_client_;
    ros::ServiceClient return_reward_client_;
    ros::Subscriber    gazebo2world_sub_;
    ros::Subscriber    terminal2robot_sub_;
    ros::Publisher     robot2gazebo_pub_;
    ros::Publisher     allocation2terminal_pub_;
    ros::Publisher     robot2task_pub_;
    ros::Publisher     drawing_pub_;
    ros::Timer         allocation_timer_;
    ros::NodeHandle*   nh_;
};

#endif // TASK_ALLOCATION_H
