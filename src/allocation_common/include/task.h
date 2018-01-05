#ifndef TASK_H
#define TASK_H

#include <DPoint.hpp>

class Task
{
public:
    bool isTarget_;
    bool isvalid_;
    int  target_power_;                     //the counteractive power of target
    int  current_power_;                    //the current counteractive power that agent know
    int  which_agent_;                      //which agent is allocated to this task
    DPoint task_pos_;                       //the position of this task

public:
    Task()
    {
        isTarget_=false;
        isvalid_=true;
        target_power_=0;
        current_power_=0;
        task_pos_=DPoint(0,0);
        which_agent_=-1;
    }
};

#endif // TASK_H
