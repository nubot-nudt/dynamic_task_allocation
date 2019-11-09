#include <task_gazebo.h>
GZ_REGISTER_MODEL_PLUGIN(Task_Gazebo)

Task_Gazebo::Task_Gazebo()
{
    taskID_ = 0;
}

Task_Gazebo::~Task_Gazebo()
{
    // Removes all callbacks from the queue. Does not wait for calls currently in progress to finish.
    message_queue_.clear();
    // Disable the queue, meaning any calls to addCallback() will have no effect.
    message_queue_.disable();
    rosnode_->shutdown();
    message_callback_queue_thread_.join();

    delete rosnode_;
}

/// \brief Load the controller. Required by model plugin. Will be called secondly
void Task_Gazebo::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
    // Get the world name.
    world_ = _model->GetWorld();
    task_model_= _model;
    model_name_= _model->GetName();
    robot_namespace_ = _model->GetName();
    taskID_ = atoi(model_name_.substr(task_name.size(),2).c_str());

    // Make sure the ROS node for Gazebo has already been initialized
    if (!ros::isInitialized())
    {
        ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
                         << "Load the Gazebo system plugin 'libnubot_gazebo.so' in the gazebo_ros package)");
        return;
    }
    rosnode_ = new ros::NodeHandle();

    //Subscribers
//    ros::SubscribeOptions so = ros::SubscribeOptions::create <allocation_common::allocation_task_info>(
//                "/task_allocation/task_state_info",1, boost::bind( &Task_Gazebo::task_state_CB,this,_1),
//                ros::VoidPtr(), &message_queue_);
//    robot2task_sub_ = rosnode_->subscribe(so);

    // Custom Callback Queue Thread. Use threads to process message and service callback queue
    message_callback_queue_thread_ = boost::thread( boost::bind( &Task_Gazebo::message_queue_thread,this ) );

    // Output info
    std::cout<<model_name_.c_str()<<" has "<<task_model_->GetPluginCount()<<" plugins, "<<"taskID: "<<taskID_<<std::endl;
}


/// \brief Model Reset function. Not required by model plugin. It is triggered when the world resets.
void Task_Gazebo::Reset()
{
    taskID_ = 0;
}

/// \brief Custom message callback queue thread
void Task_Gazebo::message_queue_thread()
{
    static const double timeout = 0.01;
    while (rosnode_->ok())
    {
        // Invoke all callbacks currently in the queue. If a callback was not ready to be called,
        // pushes it back onto the queue. This version includes a timeout which lets you specify
        // the amount of time to wait for a callback to be available before returning.
        message_queue_.callAvailable(ros::WallDuration(timeout));
    }
}

/// \brief according to the current robot state which allocated this task, change the task state
//void Task_Gazebo::task_state_CB(const allocation_common::allocation_task_info::ConstPtr &_msg)
//{
//    msgCB_lock_.lock();
//    math::Pose obs_position;

//    if(_msg->task_ID!=taskID_)
//        return;
//    else if(_msg->iscomplete)
//    {
//        obs_position=math::Pose(math::Vector3(10,10,0), math::Quaternion(0,0,0));
//        task_model_->SetWorldPose(obs_position);
//    }
//    else if(_msg->istarget)
//    {

//    }
//    msgCB_lock_.unlock();
//}
