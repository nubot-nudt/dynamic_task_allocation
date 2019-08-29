#include <robot_gazebo.h>
GZ_REGISTER_MODEL_PLUGIN(Robot_Gazebo)

Robot_Gazebo::Robot_Gazebo()
{
    robotID_=0;
    Vx_cmd_=Vy_cmd_=w_cmd_=0;
    unitX_world_=XUNIT_VECTOR;
    unitY_world_=YUNIT_VECTOR;
}

Robot_Gazebo::~Robot_Gazebo()
{
    message_queue_.clear();
    // Disable the queue, meaning any calls to addCallback() will have no effect.
    message_queue_.disable();
    rosnode_->shutdown();
    message_callback_queue_thread_.join();

    delete rosnode_;
}

/// \brief Load the controller. Required by model plugin. Will be called secondly
void Robot_Gazebo::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
    // Get the world name.
    world_ = _model->GetWorld();
    robot_model_= _model;
    model_name_ = _model->GetName();
    robot_namespace_ = _model->GetName();
    robotID_ = atoi(model_name_.substr(robot_name.size(),1).c_str());

    // Make sure the ROS node for Gazebo has already been initialized
    if (!ros::isInitialized())
    {
        ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
                         << "Load the Gazebo system plugin 'libnubot_gazebo.so' in the gazebo_ros package)");
        return;
    }
    rosnode_ = new ros::NodeHandle();

    // Subscribers.
    ros::SubscribeOptions so = ros::SubscribeOptions::create <allocation_common::robot2gazebo_info>(
                robot_namespace_+"/task_allocation/robot2gazebo_info", 100, boost::bind( &Robot_Gazebo::robot2gazebo_CB,this,_1),
                ros::VoidPtr(), &message_queue_);
    robot2gazebo_sub_ = rosnode_->subscribe(so);

    // Custom Callback Queue Thread. Use threads to process message and service callback queue
    message_callback_queue_thread_ = boost::thread( boost::bind( &Robot_Gazebo::message_queue_thread,this ) );

    // Output info
    std::cout<<model_name_.c_str()<<" has "<<robot_model_->GetPluginCount()<<" plugins, "<<"robotID: "<<robotID_<<std::endl;
}


/// \brief Model Reset function. Not required by model plugin. It is triggered when the world resets.
void Robot_Gazebo::Reset()
{
    // Variables initialization
    desired_rot_vector_ = ZERO_VECTOR;
    desired_trans_vector_ = ZERO_VECTOR;
    unitX_world_ = XUNIT_VECTOR;
    unitY_world_ = YUNIT_VECTOR;
    Vx_cmd_=Vy_cmd_=w_cmd_=0;
}

/// \brief Custom message callback queue thread
void Robot_Gazebo::message_queue_thread()
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

void Robot_Gazebo::robot_control()
{

}

/// \brief Dynmaic recofigure calback function
//void Robot_Gazebo::config(allocation_gazebo::Robot_GazeboConfig &config, uint32_t level)
//{
//    dribble_P_      = config.P;
//    dribble_I_      = config.I;
//    dribble_D_      = config.D;
//    I_term_max_     = config.I_max;
//    I_term_min_     = config.I_min;
//    ROS_FATAL("Reconfig request: P:%f I:%f D:%f I_term_max:%f I_term_min:%f",
//              dribble_P_, dribble_I_, dribble_D_, I_term_max_, I_term_min_);
//}

/// \brief VelCmd message CallBack function
/// \param[in] cmd VelCmd msg shared pointer
void Robot_Gazebo::robot2gazebo_CB(const allocation_common::robot2gazebo_info::ConstPtr &_msg)
{
    msgCB_lock_.lock();

    // the robot is damage
    if(_msg->current_mode==DAMAGE||_msg->current_mode==RESET)
        robot_model_->Reset();
    Vx_cmd_ = _msg->robot_twist.linear.x;
    Vy_cmd_ = _msg->robot_twist.linear.y;
    w_cmd_  = _msg->robot_twist.angular;

    math::Vector3 Vx_robot     = Vx_cmd_*unitX_world_;
    math::Vector3 Vy_robot     = Vy_cmd_*unitY_world_;
    math::Vector3 linear_vector= Vx_robot + Vy_robot;
    math::Vector3 angular_vector(0,0,w_cmd_);

//        ROS_FATAL("%s vel_cmd_CB():linear_vector:%f %f %f angular_vector:0 0 %f",model_name_.c_str(),
//                        linear_vector.x, linear_vector.y, linear_vector.z, angular_vector.z);
    robot_locomotion(linear_vector, angular_vector);

    msgCB_lock_.unlock();
}

/// \brief according to the topic from robot allocation node, move the model in the Gazebo
void Robot_Gazebo::robot_locomotion(math::Vector3 linear_vel_vector, math::Vector3 angular_vel_vector)
{
    //robots is on the ground, so the vector.z of linear velocity is 0
    desired_trans_vector_ = linear_vel_vector;
    desired_trans_vector_.z = 0;

    //robots is on the ground, so the vector.x vector.y of angular velocity is 0
    desired_rot_vector_   = angular_vel_vector;
    desired_rot_vector_.x = 0;
    desired_rot_vector_.y = 0;

    robot_model_->SetLinearVel(desired_trans_vector_);
    robot_model_->SetAngularVel(desired_rot_vector_);
}
