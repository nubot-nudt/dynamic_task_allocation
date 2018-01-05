#include "task_allocation.h"

int main(int argc, char **argv)
{
    ros::init(argc,argv,"task_allocation_node");
    ros::Time::init();
    Task_Allocation Task_Allocation(argc,argv);
    ros::spin();
    return 0;
}

