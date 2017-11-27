#ifndef AGENT_H
#define AGENT_H

#include <DPoint.hpp>
#include <qvector.h>

class Agent
{
public:
    Agent();

public:
    bool isvaild_;
    int  power_;                    //the adjective power of this agent
    int  which_task_;               //which task is allocated to this agent
    int  which_target_;             //which target is allocated to this agent
    int  last_drop_task_;           //last dropped task
    int  last_drop_target_;         //last dropped target
    int  mode_;                     //0 no task,1 get task,2 do task,3 explore region,4 assail target,5 destroyed
    DPoint2i init_agent_pos_;
    DPoint2i agent_pos_;

    QVector<int> task_vec_;         //the list of the task
    QVector<int> target_vec_;       //the list of the target
    QVector<int> task_cost_;        //the list of the task cost
    QVector<int> target_cost_;      //the list of the target cost
};

#endif // AGENT_H
