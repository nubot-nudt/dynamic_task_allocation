#include "task.h"

Task::Task()
{
    isTarget_=false;
    isvaild_=true;
    target_power_=0;
    current_power_=0;
    task_pos_=DPoint2i(0,0);
    which_agent_=-1;
}
