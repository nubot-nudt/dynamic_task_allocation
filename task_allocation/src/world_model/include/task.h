#ifndef TASK_H
#define TASK_H

#include <DPoint.hpp>

class Task
{
public:
    Task();

public:
    bool isTarget_;
    bool isvaild_;
    int  target_power_;                     //the counteractive power of target
    int  current_power_;                    //the current counteractive power that agent know
    int  which_agent_;                      //which agent is allocated to this task
    DPoint2i task_pos_;                     //the position of this task
};

#endif // TASK_H
