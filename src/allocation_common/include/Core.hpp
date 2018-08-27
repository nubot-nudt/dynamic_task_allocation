#ifndef CORE_HPP
#define CORE_HPP

#include <Circle.hpp>
#include <Line.hpp>
#include <PPoint.hpp>
#include <DPoint.hpp>
#include <Angle.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <ros/ros.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
	
#define MAXNUM_AGENT 10
#define LOCATION_ERROR 0.2
#define EXPLORE_TIME 30              //the time explore process will spend
#define HIT_TIME 30                  //the time hit process will spend

enum Robots_mode
{
    IDLE,                            //has nothing to do
    PLAN,                            //make a plan to complete a task
    EXECUTE,                         //execute the task
    EXPLORE,                         //explore the unknown region
    HIT,                             //hit the target region
    DAMAGE,                          //robot is damaged
    RESET                            //reset the robot
};

enum Reward_causes
{
    Invalid_task,                    //the allocated task has been complete
    Drop_task,                       //drop the task halfway
    Complete_target,                 //complete a target
    Explore_task,                    //explore a task
    Robot_damage
};

enum Allocation_mode
{
    ALLOCATION_START,
    ALLOCATION_PAUSE,
    ALLOCATION_STOP
};

enum Allocation_method
{
    Prediction,
    Market,
    DQN
};

struct Gazebo_robot_info
{
    /// these information are obtained from gazebo
    int    robot_ID;
    DPoint robot_pos;
    double robot_ori;
    DPoint robot_vel;
    double robot_w;
};

struct Gazebo_task_info
{
    /// these information are obtained from gazebo
    int    task_ID;
    DPoint task_pos;
};

struct Allocation_robot_info
{
    /// these information are obtained form control_terminal
    int    robot_power;
    /// these information are obtained from task_allocation
    int    robot_ID;
    char   robot_mode;   
    float  move_distance;
    bool   isvalid;
    /// for the prediction method
    int    which_task;
    int    which_target;
    /// for the market-base method
    DPoint expect_pos;
    vector<int> target_list;
    vector<int> task_list;

    Allocation_robot_info()
    {
        robot_power=0;
        robot_ID=0;
        robot_mode=IDLE;
        which_task=-1;
        which_target=-1;
        target_list.clear();
        task_list.clear();
        expect_pos=DPoint(-100,-100);    //the (-100,-100) is an initialzation and has no mean
        move_distance=0;
        isvalid=true;
    }
    void robot_reset()
    {
        robot_mode=RESET;
        which_task=-1;
        which_target=-1;
        target_list.clear();
        task_list.clear();
        expect_pos=DPoint(-100,-100);
        move_distance=0;
        isvalid=true;
    }
};

struct Allocation_task_info
{
    /// these information are obtained form control_terminal
    int    task_power;
    /// these information are obtained from task_allocation
    int    task_ID;
    int    known_power;
    bool   istarget;
    double current_distance;
    bool   iscomplete;
    bool   isexplored;
    bool   isallocated;
    Allocation_task_info()
    {
        task_power=0;
        task_ID=0;
        known_power=0;
        current_distance=1000;
        istarget=false;
        iscomplete=false;
        isexplored=false;
        isallocated=false;
    }
    void task_reset()
    {
        known_power=0;
        current_distance=1000;
        istarget=false;
        iscomplete=false;
        isexplored=false;
        isallocated=false;
    }
};

struct Robot_info
{
    Gazebo_robot_info gazebo_robot_info;
    Allocation_robot_info allocation_robot_info;
};

struct Task_info
{
    Gazebo_task_info gazebo_task_info;
    Allocation_task_info allocation_task_info;
};

struct Terminal2Gazebo_info
{
    std::vector<int>  robot_pos_x;
    std::vector<int>  robot_pos_y;
    std::vector<int>  task_pos_x;
    std::vector<int>  task_pos_y;
    bool is_noise;
    bool isNew_allocation;
};

struct Terminal2Robots_info
{
    char allocation_mode;              //start 1, stop 0
    bool greedorprobability;           //greed 0, probability 1
//    bool marketorprediction;           //market 0, prediction 1
    char allocation_method;            //prediction 0, market 1, DQN 2

    std::vector<Allocation_robot_info> all_allocation_robot_info;
    std::vector<Allocation_task_info> all_allocation_task_info;
};

struct Gazebo2World_info
{
    std::vector<Gazebo_robot_info> gazebo_robots_info;
    std::vector<Gazebo_task_info>  gazebo_tasks_info;
};
#endif //CORE_HPP
