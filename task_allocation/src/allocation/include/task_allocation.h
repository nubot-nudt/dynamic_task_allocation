#ifndef TASK_ALLOCATION_H
#define TASK_ALLOCATION_H

#include <ros/ros.h>
#include <agent.h>
#include <task.h>

class Task_Allocation
{
public:
    Task_Allocation(int argc, char **argv);
    Agent my_agent_;                             //agent item
    Task  my_task_;                              //task item

public:
    bool greedorprobability_;                    //greed 0, probability 1
    bool recordornot_;                           //not record 0, record 1
    bool powerordistance_;                       //power 0, distance 1
    bool mutativeorconstant_;                    //mutative 0, constant 1
};

#endif // TASK_ALLOCATION_H
