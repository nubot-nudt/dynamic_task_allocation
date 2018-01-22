#include <world_gazebo.h>
GZ_REGISTER_WORLD_PLUGIN(World_Gazebo)

World_Gazebo::World_Gazebo()
{
    model_count_ = 0;
    ModelStatesCB_flag_ = false;

    noise_scale_ = 0.0;
    noise_rate_ = 0.0;

    // Resize message fields
    model_states_.name.reserve(50);
    model_states_.pose.reserve(50);
    model_states_.twist.reserve(50);
}

World_Gazebo::~World_Gazebo()
{
    event::Events::DisconnectWorldUpdateBegin(update_connection_);
    // Removes all callbacks from the queue. Does not wait for calls currently in progress to finish.
    message_queue_.clear();
    // Disable the queue, meaning any calls to addCallback() will have no effect.
    message_queue_.disable();
    rosnode_->shutdown();
    message_callback_queue_thread_.join();

    delete rosnode_;
}

/// \brief Load the controller. Required by world plugin. Will be called secondly
void World_Gazebo::Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
{
    // Get the world name.
    world_ = _world;
    world_name_=_world->GetName();

    // Make sure the ROS node for Gazebo has already been initialized
    if (!ros::isInitialized())
    {
        ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
                         << "Load the Gazebo system plugin 'libnubot_gazebo.so' in the gazebo_ros package)");
        return;
    }
    rosnode_ = new ros::NodeHandle();
    // this node is for robot model spawn
    node_=transport::NodePtr(new transport::Node());
    node_->Init(world_name_);

    // Publishers
    gazebo2world_pub_ = rosnode_->advertise<allocation_common::gazebo2world_info>("allocation_gazebo/gazebo2world_info",10);
    debug_pub_ = rosnode_->advertise<std_msgs::Float64MultiArray>("debug",10);
    factoryPub_ = node_->Advertise<msgs::Factory>("~/factory");

    // Subscribers.
    ros::SubscribeOptions so = ros::SubscribeOptions::create <gazebo_msgs::ModelStates>(
                "/gazebo/model_states", 100, boost::bind( &World_Gazebo::model_states_CB,this,_1),
                ros::VoidPtr(), &message_queue_);
    ModelStates_sub_ = rosnode_->subscribe(so);

    ros::SubscribeOptions so1 = ros::SubscribeOptions::create <allocation_common::terminal2gazebo_info>(
                "/control_terminal/terminal2gazebo_info", 100, boost::bind( &World_Gazebo::terminal_info_CB,this,_1),
                ros::VoidPtr(), &message_queue_);
    terminal2gazebo_sub_ = rosnode_->subscribe(so1);

    // Custom Callback Queue Thread. Use threads to process message and service callback queue
    message_callback_queue_thread_ = boost::thread( boost::bind( &World_Gazebo::message_queue_thread,this ) );

    // This event is broadcast every simulation iteration.
    update_connection_ = event::Events::ConnectWorldUpdateBegin(boost::bind(&World_Gazebo::update_child, this));

    // Output info
    std::cout<<world_name_.c_str()<<" initialize, "<<"gaussian_noise -- scale: "<<noise_scale_<<" rate: "<<noise_rate_<<std::endl;
}


/// \brief Model Reset function. Not required by model plugin. It is triggered when the world resets.
void World_Gazebo::Reset()
{
    // Variables initialization
    unitX_robot_ = XUNIT_VECTOR;
    ModelStatesCB_flag_ = false;
}

/// \brief Custom message callback queue thread
void World_Gazebo::message_queue_thread()
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

/// \brief Custom message callback queue thread
void World_Gazebo::model_states_CB(const gazebo_msgs::ModelStates::ConstPtr& _msg)
{
    msgCB_lock_.lock();
    // model_states is callback, the model info can be update
    ModelStatesCB_flag_ = true;
    model_count_ = 0;
    model_states_.name.clear();
    model_states_.pose.clear();
    model_states_.twist.clear();

    for(int i=0; i<world_->GetModelCount() ;i++)
    {
        // get info of robots and tasks, reference frame: world
        if(_msg->name[i].find(robot_name)!=std::string::npos||_msg->name[i].find(task_name)!=std::string::npos)
        {
            geometry_msgs::Pose     ps = _msg->pose[i];
            geometry_msgs::Twist    tw = _msg->twist[i];
            // add gaussian noise
            ps.position.x += noise(noise_scale_, noise_rate_);
            ps.position.y += noise(noise_scale_, noise_rate_);
            // if the robots are move in 3D space
            // ps.position.z += noise(noise_scale_, noise_rate_);
            tw.linear.x   += noise(noise_scale_, noise_rate_);
            tw.linear.y   += noise(noise_scale_, noise_rate_);
            // tw.linear.z   += noise(noise_scale_, noise_rate_);

            model_states_.name.push_back(_msg->name[i]);
            model_states_.pose.push_back(ps);
            model_states_.twist.push_back(tw);

            model_count_ ++;
        }
    }
    msgCB_lock_.unlock();
}

/// \brief terminal information CB, about the position and num of tasks or robots
void World_Gazebo::terminal_info_CB(const allocation_common::terminal2gazebo_info::ConstPtr &_msg)
{
    msgCB_lock_.lock();
    std::string task_name;
    std::string task_pose;

    if(_msg->is_noise)
    {
        noise_rate_=0.05;
        noise_scale_=0.03;
    }
    // each robot has different model, so we can use the factory msg to spwan robot model
    msgs::Factory  factory_msg;
    for(int i=0;i<_msg->robot_pos_x.size();i++)
    {
        // Model file to load
        factory_msg.set_sdf_filename("model://Robot"+std::to_string(i));
        // Pose to initialize the model to world
        msgs::Set(factory_msg.mutable_pose(),ignition::math::Pose3d(ignition::math::Vector3d(_msg->robot_pos_x[i],_msg->robot_pos_y[i],0),ignition::math::Quaterniond(0, 0, 0)));
        // Send the message
        factoryPub_->Publish(factory_msg);
    }

    // because the model of task is same, so we must modify the name of it before it register
    sdf::SDF TaskSDF;
    TaskSDF.SetFromString(
                "<sdf version='1.6'>\
                <model name='Task'>\
            <pose>1 0 0 0 0 0</pose>\
            <static>true</static>\
            <link name='chassis'>\
            <pose>0 0 0 0 0 0</pose>\
            <collision name='collision'>\
            <pose>0 0 0 0 0 0</pose>\
            <geometry>\
            <mesh>\
            <scale>1 1 1</scale>\
            <uri>file://meshes/task.dae</uri>\
            </mesh>\
            </geometry>\
            </collision>\
            <visual name='visual'>\
            <pose>0 0 0 0 0 0</pose>\
            <geometry>\
            <mesh>\
            <scale>1 1 1</scale>\
            <uri>file://meshes/task.dae</uri>\
            </mesh>\
            </geometry>\
            </visual>\
            </link>\
            <plugin name='task_gazebo' filename='libtask_gazebo.so' />\
            </model>\
            </sdf>");

    for(int i=0;i<_msg->task_pos_x.size();i++)
    {
        // set different name for each task (Task i)
        task_name="Task"+std::to_string(i);
        sdf::ElementPtr model = TaskSDF.Root()->GetElement("model");
        model->GetAttribute("name")->SetFromString(task_name);
        // set different pose for each task (pos_x pos_y 0 0 0 0)
        task_pose=std::to_string(_msg->task_pos_x[i])+" "+std::to_string(_msg->task_pos_y[i])+" 0 0 0 0";
        sdf::ElementPtr pose = model->GetElement("pose");
        pose->AddValue("pose",task_pose,false,"new pose for different tasks");
        world_->InsertModelSDF(TaskSDF);
    }

//    for(unsigned int i=0;i<_msg->all_allocation_task_info.size();i++)
//        if(_msg->all_allocation_task_info[i].iscomplete)
//            destroy_tasks_.push_back(_msg->all_allocation_task_info[i].task_ID);
//    for(unsigned int i=0;i<_msg->all_allocation_robot_info.size();i++)
//        if(!_msg->all_allocation_robot_info[i].isvalid)
//            destroy_robots_.push_back(_msg->all_allocation_robot_info[i].robot_ID);

    msgCB_lock_.unlock();
}

/// \brief  Updating models' states
/// \return 1: updating model info success 0: not success
bool World_Gazebo::update_model_info(void)
{
    allocation_common::gazebo2world_info    _gazebo2world_info;

    if(ModelStatesCB_flag_)
    {
        for(int i=0; i<model_count_;i++)
        {
            // tasks info, compare model name' prefix to determine tasks
            // the origin of task is the angular, change it to the center
            if(model_states_.name[i].compare(0, task_name.size(), task_name) == 0)
            {
                int task_id= atoi(model_states_.name[i].substr(task_name.size(),2).c_str());
                geometry_msgs::Pose  task_pose = model_states_.pose[i];

                tasks_info_.task_ID = task_id;
                tasks_info_.task_pose.x  = task_pose.position.x+0.5;
                tasks_info_.task_pose.y  = task_pose.position.y+0.5;

                _gazebo2world_info.gazebo_tasks_info.push_back(tasks_info_);
            }

            // robots info
            else if(model_states_.name[i].compare(0, robot_name.size(), robot_name)==0)
            {
                int robot_id = atoi(model_states_.name[i].substr(robot_name.size(),1).c_str());

                geometry_msgs::Pose  robot_pose  = model_states_.pose[i];
                geometry_msgs::Twist robot_twist = model_states_.twist[i];
                math::Quaternion rot_qua(robot_pose.orientation.w, robot_pose.orientation.x,
                                         robot_pose.orientation.y, robot_pose.orientation.z);
                double heading_theta = rot_qua.GetYaw();
                robots_info_.robot_ID              = robot_id;
                robots_info_.robot_pose.position.x = robot_pose.position.x;
                robots_info_.robot_pose.position.y = robot_pose.position.y;
                robots_info_.robot_pose.theta      = heading_theta;
                robots_info_.robot_twist.angular   = robot_twist.angular.z;
                robots_info_.robot_twist.linear.x  = robot_twist.linear.x;
                robots_info_.robot_twist.linear.y  = robot_twist.linear.y;

                _gazebo2world_info.gazebo_robots_info.push_back(robots_info_);
            }
        }
        gazebo2world_pub_.publish(_gazebo2world_info);
        ModelStatesCB_flag_=false;
        return 1;
    }
    else
        return 0;
}

/// \brief return a value representing real world noise. The noise complies with Normal(gaussian) distribution
/// \param[in] scale            the magnitude of the noise is within [0, scale]
/// \param[in] probability      the probability of generating noise, probability should be in [0,1]
double World_Gazebo::noise(double scale, double probability)
{
    if(math::equal<double>(scale, 0.0))
        return 0.0;
    else
    {
        if(rand_.GetIntUniform(0,10) <= (int)10.0*probability)
            return scale*rand_.GetDblNormal(0,1);
        else
            return 0.0;
    }
}

/// \brief Update the controller. It is running every simulation iteration.
/// [realtime factor] = [realtime update rate] * [max step size].
void World_Gazebo::update_child()
{
    //lock access to fields that are used in ROS message callbacks
    msgCB_lock_.lock();
    if(!update_model_info());
        // std::cout<<"update_model_info(): Waiting for model_states messages!"<<std::endl;
    msgCB_lock_.unlock();
}
