#include "ros/ros.h"
#include "allocation_common/GetAction.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "GetAction");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<allocation_common::GetAction>("dqn_ros/get_action");
    allocation_common::GetAction srv;
    srv.request.observation.Agent_ID=1;
    srv.request.observation.robot_pos.x=5;
    srv.request.observation.robot_pos.y=5;
    allocation_common::Teammateinfo teammateinfo;
    teammateinfo.robot_pos.x=2;
    teammateinfo.robot_pos.y=2;
    teammateinfo.which_task=10;
    srv.request.observation.teammatesinfo.push_back(teammateinfo);
    teammateinfo.robot_pos.x=3;
    teammateinfo.robot_pos.y=3;
    teammateinfo.which_task=11;
    srv.request.observation.teammatesinfo.push_back(teammateinfo);

    allocation_common::Taskinfo taskinfo;
    for (int i; i<10; i++)
    {
        taskinfo.task_pos.x=i;
        taskinfo.task_pos.y=2*i;
        taskinfo.task_status=0;
        srv.request.observation.tasksinfo.push_back(taskinfo);
    }

    if (client.call(srv))
    {
        if (srv.response.action==-1)
        {
            ROS_ERROR("Failed to call service");
            return 1;
        }

        ROS_INFO("action: %d", (int)srv.response.action);
    }
    else
    {
        ROS_ERROR("Failed to call service");
        return 1;
    }

    return 0;
}
