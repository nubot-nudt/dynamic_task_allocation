#include "agent.h"

Agent::Agent()
{
    isvaild_=true;
    power_=0;
    init_agent_pos_=DPoint2i(0,0);
    agent_pos_=DPoint2i(0,0);
    which_task_=-1;
    which_target_=-1;
    last_drop_task_=-1;
    last_drop_target_=-1;
    mode_=0;
}
