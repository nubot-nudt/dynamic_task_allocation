#include "task_allocation.h"

Task_Allocation::Task_Allocation(int argc,char** argv)
{
    const char * environment;
    std::string agent_ID = argv[1];
    //std::string robot_prefix = agent_ID.substr(0,agent_ID.size()-1);
    environment = agent_ID.c_str();
    ROS_INFO("start Agent%s task_allocation_process",agent_ID.c_str());
}
