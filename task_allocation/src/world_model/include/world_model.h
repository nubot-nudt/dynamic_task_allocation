#ifndef WORLD_MODEL_H
#define WORLD_MODEL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <ros/ros.h>
#include <boost/thread.hpp>
#include <task.h>
#include <agent.h>
#include <qvector.h>

class World_Model
{
public:
    World_Model(int argc,char** argv);
    ~World_Model();

public:
    QVector<Agent> all_agents_;                  //record agent parameters
    QVector<Task>  all_tasks_;                   //record task parameters
    QVector<Task>  all_targets_;                 //record target parameters

    QVector<Agent> init_agents_;                 //record initial agent parameters
    QVector<Task>  init_tasks_;                  //record initial task parameters

    QVector<int>   lab_agent_;                   //record the number of agent that choose

    int num_task_vaild_;                         //the number of task that uncompleted
    int num_target_vaild_;                       //the number of target that had not been destroyed
    int num_agent_vaild_;                        //the number of agent vaild
};

#endif // WORLD_MODEL_H
