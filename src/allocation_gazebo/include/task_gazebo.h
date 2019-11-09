#ifndef TASK_GAZEBO_H
#define TASK_GAZEBO_H

#include "gazebo_info.h"

class Task_Gazebo : public gazebo::ModelPlugin
{
private:

    physics::WorldPtr                   world_;                              //a pointer to the gazebo world.
    physics::ModelPtr                   task_model_;                         //pointer to the robot model

    ros::NodeHandle*                    rosnode_;
    ros::Subscriber                     robot2task_sub_;

    boost::thread                       message_callback_queue_thread_;      //thead object for the running callback Thread.
    boost::mutex                        msgCB_lock_;                         //a mutex to lock access to fields that are used in ROS message callbacks
    ros::CallbackQueue                  message_queue_;                      //custom Callback Queue

    ignition::math::Rand                rand_;

    std::string                         model_name_;
    std::string                         robot_namespace_;
    int                                 taskID_;
    std::vector<int>                    destroy_tasks_;                      //the task which have been destroyed

public:
    Task_Gazebo();
    virtual ~Task_Gazebo();
    void    message_queue_thread();
//    void    task_state_CB(const allocation_common::allocation_task_info::ConstPtr & _msg);
    
protected:
    void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/);
    virtual void Reset();
};

#endif //! TASK_GAZEBO_H
