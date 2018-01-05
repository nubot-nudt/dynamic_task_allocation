#ifndef AGENT_H
#define AGENT_H

#include <DPoint.hpp>

class Agent
{
public:
    bool isvalid_;
    int  power_;                    //the adjective power of this agent
    int  which_task_;               //which task is allocated to this agent
    int  which_target_;             //which target is allocated to this agent
    int  last_drop_task_;           //last dropped task
    int  last_drop_target_;         //last dropped target
    int  mode_;                     //0 no task,1 get task,2 do task,3 explore region,4 assail target,5 destroyed
    DPoint init_agent_pos_;
    DPoint agent_pos_;

    std::vector<int> task_vec_;         //the list of the task
    std::vector<int> target_vec_;       //the list of the target
    std::vector<int> task_cost_;        //the list of the task cost
    std::vector<int> target_cost_;      //the list of the target cost

public:
    Agent()
    {
        isvalid_=true;
        power_=0;
        init_agent_pos_=DPoint(0,0);
        agent_pos_=DPoint(0,0);
        which_task_=-1;
        which_target_=-1;
        last_drop_task_=-1;
        last_drop_target_=-1;
        mode_=0;
    }
};
#endif // AGENT_H
