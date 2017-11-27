// NOTICE:
// GAZEBO uses ISO units, i.e. length uses meters.
// but other code uses cm as the length unit, so for publishing
// and subscribing messages, length unit should be changed to 'cm'

#include <algorithm>
#include <assert.h>
#include <cmath>
#include "nubot_gazebo.hh"
#include "vector_angle.hh"

#define RUN 1
#define FLY -1
#define ZERO_VECTOR math::Vector3::Zero
#define PI 3.14159265

#define CM2M_CONVERSION 0.01
#define M2CM_CONVERSION 100

enum {NOTSEEBALL = 0, SEEBALLBYOWN = 1,SEEBALLBYOTHERS = 2};
const math::Vector3 kick_vector_robot(1,0,0);    // assume the normalized vector from origin to kicking mechanism in robot refercence frame
// is in x-axis direction
const double goal_x = 9.0;
const double goal_height = 1.0;
const double g = 9.8;
const double m = 0.41;                   // ball mass (kg)
const double eps = 0.0001;                      // small value

using namespace gazebo;
GZ_REGISTER_MODEL_PLUGIN(NubotGazebo)

NubotGazebo::NubotGazebo()
{
    // Variables initialization
    desired_rot_vector_ = ZERO_VECTOR;
    desired_trans_vector_ = ZERO_VECTOR;
    nubot_ball_vec_ = math::Vector3(1,0,0);
    kick_vector_world_ = kick_vector_robot;
    nubot_ball_vec_len_ = 1;
    ball_index_=robot_index_=0;
    Vx_cmd_=Vy_cmd_=w_cmd_=0;
    force_ = 0.0; mode_=1;

    model_count_ = 0;
    dribble_flag_ = false;
    shot_flag_ = false;
    ModelStatesCB_flag_ = false;
    judge_nubot_stuck_ = false;
    is_kick_ = false;
    flip_cord_ = false;
    AgentID_ = 0;
    noise_scale_ = 0.0;
    noise_rate_ = 0.0;
    state_ = CHASE_BALL;
    sub_state_ = MOVE_BALL;

    obs_ = new Obstacles();
    if(!obs_)
        ROS_FATAL("Cannot allocate memory to type Obstacles!");

    // Resize message fields
    model_states_.name.reserve(20);
    model_states_.pose.reserve(20);
    model_states_.twist.reserve(20);
}

NubotGazebo::~NubotGazebo()
{
    event::Events::DisconnectWorldUpdateBegin(update_connection_);
    // Removes all callbacks from the queue. Does not wait for calls currently in progress to finish.
    message_queue_.clear();
    service_queue_.clear();
    // Disable the queue, meaning any calls to addCallback() will have no effect.
    message_queue_.disable();
    service_queue_.disable();
    rosnode_->shutdown();                     // This MUST BE CALLED before thread join()!!
    message_callback_queue_thread_.join();
    service_callback_queue_thread_.join();

    delete rosnode_;
    delete obs_;
}

void NubotGazebo::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
    // Get the world name.
    world_ = _model->GetWorld();
    robot_model_ = _model;
    model_name_ = robot_model_->GetName();
    robot_namespace_ = robot_model_->GetName();

    // Make sure the ROS node for Gazebo has already been initialized
    if (!ros::isInitialized())
    {
        ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
                         << "Load the Gazebo system plugin 'libnubot_gazebo.so' in the gazebo_ros package)");
        return;
    }
    rosnode_ = new ros::NodeHandle(robot_namespace_);
    rosnode_->param<std::string>("/football/name",                   ball_name_,            std::string("football") );
    rosnode_->param<std::string>("/football/chassis_link",           ball_chassis_,         std::string("football::ball") );
    rosnode_->param<std::string>("/cyan/prefix",                     cyan_pre_,             std::string("nubot"));
    rosnode_->param<std::string>("/magenta/prefix",                  mag_pre_,              std::string("rival"));
    rosnode_->param<double>("/general/dribble_distance_thres",  dribble_distance_thres_,    0.50);
    rosnode_->param<double>("/general/dribble_angle_thres",     dribble_angle_thres_,       30.0);
    rosnode_->param<double>("/field/length",                    field_length_,              18.0);
    rosnode_->param<double>("/field/width",                     field_width_,               12.0);
    rosnode_->param<double>("/general/noise_scale",             noise_scale_,               0.10);
    rosnode_->param<double>("/general/noise_rate",              noise_rate_,                0.01);

    if(!_sdf->HasElement("flip_cord"))
    {
        ROS_INFO("NubotGazebo plugin missing <flip_cord>, defaults to false");
        flip_cord_ = false;
    }
    else
        flip_cord_ = _sdf->GetElement("flip_cord")->Get<bool>();

    AgentID_ = atoi( model_name_.substr(cyan_pre_.size(),1).c_str() );    // get the robot id

    // Load the football model
    ball_model_ = world_->GetModel(ball_name_);
    if (!ball_model_)
        ROS_ERROR("model [%s] does not exist", ball_name_.c_str());
    else
    {
        ball_link_ = ball_model_->GetLink(ball_chassis_);
        if(!ball_link_)
            ROS_ERROR("link [%s] does not exist!", ball_chassis_.c_str());
    }

    // Publishers
    omin_vision_pub_   = rosnode_->advertise<nubot_common::OminiVisionInfo>("omnivision/OmniVisionInfo",10);
    debug_pub_ = rosnode_->advertise<std_msgs::Float64MultiArray>("debug",10);

    // Subscribers.
    ros::SubscribeOptions so1 = ros::SubscribeOptions::create<gazebo_msgs::ModelStates>(
                "/gazebo/model_states", 100, boost::bind( &NubotGazebo::model_states_CB,this,_1),
                ros::VoidPtr(), &message_queue_);
    ModelStates_sub_ = rosnode_->subscribe(so1);

    ros::SubscribeOptions so2 = ros::SubscribeOptions::create<nubot_common::VelCmd>(
                "nubotcontrol/teleop_joy", 100, boost::bind( &NubotGazebo::vel_cmd_CB,this,_1),
                ros::VoidPtr(), &message_queue_);
    Velcmd_sub_ = rosnode_->subscribe(so2);

    ros::SubscribeOptions so3 = ros::SubscribeOptions::create<nubot_common::Pos2d>(
                "obs_position", 100, boost::bind( &NubotGazebo::obs_position,this,_1),
                ros::VoidPtr(), &message_queue_);
    Obspos_sub_ = rosnode_->subscribe(so3);

    // Service Servers
    ros::AdvertiseServiceOptions aso1 = ros::AdvertiseServiceOptions::create<nubot_common::BallHandle>(
                "BallHandle", boost::bind(&NubotGazebo::ball_handle_control_service, this, _1, _2),
                ros::VoidPtr(), &service_queue_);
    ballhandle_server_ =   rosnode_->advertiseService(aso1);

    ros::AdvertiseServiceOptions aso2 = ros::AdvertiseServiceOptions::create<nubot_common::Shoot>(
                "Shoot", boost::bind(&NubotGazebo::shoot_control_servive, this, _1, _2),
                ros::VoidPtr(), &service_queue_);
    shoot_server_ =   rosnode_->advertiseService(aso2);

#if 0
    reconfigureServer_ = new dynamic_reconfigure::Server<nubot_gazebo::NubotGazeboConfig>(*rosnode_);
    reconfigureServer_->setCallback(boost::bind(&NubotGazebo::config, this, _1, _2));
#endif

    // Custom Callback Queue Thread. Use threads to process message and service callback queue
    message_callback_queue_thread_ = boost::thread( boost::bind( &NubotGazebo::message_queue_thread,this ) );
    service_callback_queue_thread_ = boost::thread( boost::bind( &NubotGazebo::service_queue_thread,this ) );

    // This event is broadcast every simulation iteration.
    update_connection_ = event::Events::ConnectWorldUpdateBegin(
                boost::bind(&NubotGazebo::update_child, this));

    // Output info
    ROS_INFO(" %s has %d plugins\n\tid: %d \tflip_cord:%d\n\tgaussian_noise -- scale: %f\t rate: %f",
              model_name_.c_str(), robot_model_->GetPluginCount(), AgentID_, flip_cord_, noise_scale_, noise_rate_);

}

void NubotGazebo::Reset()
{
    ROS_DEBUG("%s Reset() running now!", model_name_.c_str());

    // Variables initialization
    desired_rot_vector_ = ZERO_VECTOR;
    desired_trans_vector_ = ZERO_VECTOR;
    nubot_ball_vec_ = math::Vector3(1,0,0);
    kick_vector_world_ = kick_vector_robot;
    nubot_ball_vec_len_ = 1;
    Vx_cmd_=Vy_cmd_=w_cmd_=0;
    force_ = 0.0; mode_=1;

    dribble_flag_ = false;
    shot_flag_ = false;
    ModelStatesCB_flag_ = false;
    judge_nubot_stuck_ = false;
    is_kick_ = false;
    state_ = CHASE_BALL;
    sub_state_ = MOVE_BALL;

}

void NubotGazebo::message_queue_thread()
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

void NubotGazebo::service_queue_thread()
{
    static const double timeout = 0.01;
    while (rosnode_->ok())
        service_queue_.callAvailable(ros::WallDuration(timeout));
}

void NubotGazebo::config(nubot_gazebo::NubotGazeboConfig &config, uint32_t level)
{
    dribble_P_      = config.P;
    dribble_I_      = config.I;
    dribble_D_      = config.D;
    I_term_max_     = config.I_max;
    I_term_min_     = config.I_min;
    ROS_FATAL("Reconfig request: P:%f I:%f D:%f I_term_max:%f I_term_min:%f",
              dribble_P_, dribble_I_, dribble_D_, I_term_max_, I_term_min_);
}

void NubotGazebo::model_states_CB(const gazebo_msgs::ModelStates::ConstPtr& _msg)
{
    msgCB_lock_.lock();

    ModelStatesCB_flag_ = true;
    model_count_ = 0;
    model_states_.name.clear();
    model_states_.pose.clear();
    model_states_.twist.clear();

    for(int i=0; i<world_->GetModelCount() ;i++)
    {
        // get info of robots and the ball; reference frame: world
        if( (_msg->name[i].find(cyan_pre_) != std::string::npos) ||
            (_msg->name[i].find(mag_pre_) != std::string::npos) ||
            (_msg->name[i] == ball_name_) )
        {
            geometry_msgs::Pose     ps = _msg->pose[i];
            geometry_msgs::Twist    tw = _msg->twist[i];
            ps.position.x += noise(noise_scale_, noise_rate_);  // add gaussian noise
            ps.position.y += noise(noise_scale_, noise_rate_);
            // ps.position.z += noise(noise_scale_, noise_rate_);
            tw.linear.x   += noise(noise_scale_, noise_rate_);
            tw.linear.y   += noise(noise_scale_, noise_rate_);
            // tw.linear.z   += noise(noise_scale_, noise_rate_);

            if(flip_cord_)      // rival robot model
            {
                // We only have to change the sign of x and y positions, and x and y velocities;
                // Since the coordinate frame of the rival model has been flipped, we don't have
                // to change the orientation here.
                ps.position.x *= -1.0;
                ps.position.y *= -1.0;
                tw.linear.x *= -1.0;
                tw.linear.y *= -1.0;
            }

            model_states_.name.push_back(_msg->name[i]);
            model_states_.pose.push_back(ps);
            model_states_.twist.push_back(tw);

            if(model_states_.name.back() == ball_name_ )
                ball_index_ =  model_count_;
            else if(model_states_.name.back() == model_name_)
                robot_index_ = model_count_;

            model_count_ ++;
        }
    }

    msgCB_lock_.unlock();
}

bool NubotGazebo::update_model_info(void)
{
    if(ModelStatesCB_flag_)
    {
        // Get football and nubot's pose and twist
        ball_state_.model_name = ball_name_ ;
        ball_state_.pose.position.x     = model_states_.pose[ball_index_].position.x;
        ball_state_.pose.position.y     = model_states_.pose[ball_index_].position.y;
        ball_state_.pose.position.z     = model_states_.pose[ball_index_].position.z;
        ball_state_.pose.orient.w  = model_states_.pose[ball_index_].orientation.w;
        ball_state_.pose.orient.x  = model_states_.pose[ball_index_].orientation.x;
        ball_state_.pose.orient.y  = model_states_.pose[ball_index_].orientation.y;
        ball_state_.pose.orient.z  = model_states_.pose[ball_index_].orientation.z;
        ball_state_.twist.linear.x      = model_states_.twist[ball_index_].linear.x;
        ball_state_.twist.linear.y      = model_states_.twist[ball_index_].linear.y;
        ball_state_.twist.linear.z      = model_states_.twist[ball_index_].linear.z;
        ball_state_.twist.angular.x     = model_states_.twist[ball_index_].angular.x;
        ball_state_.twist.angular.y     = model_states_.twist[ball_index_].angular.y;
        ball_state_.twist.angular.z     = model_states_.twist[ball_index_].angular.z;

        robot_state_.model_name = ball_name_ ;
        robot_state_.pose.position.x    = model_states_.pose[robot_index_].position.x;
        robot_state_.pose.position.y    = model_states_.pose[robot_index_].position.y;
        robot_state_.pose.position.z    = model_states_.pose[robot_index_].position.z;
        robot_state_.pose.orient.w = model_states_.pose[robot_index_].orientation.w;
        robot_state_.pose.orient.x = model_states_.pose[robot_index_].orientation.x;
        robot_state_.pose.orient.y = model_states_.pose[robot_index_].orientation.y;
        robot_state_.pose.orient.z = model_states_.pose[robot_index_].orientation.z;
        robot_state_.twist.linear.x     = model_states_.twist[robot_index_].linear.x;
        robot_state_.twist.linear.y     = model_states_.twist[robot_index_].linear.y;
        robot_state_.twist.linear.z     = model_states_.twist[robot_index_].linear.z;
        robot_state_.twist.angular.x    = model_states_.twist[robot_index_].angular.x;
        robot_state_.twist.angular.y    = model_states_.twist[robot_index_].angular.y;
        robot_state_.twist.angular.z    = model_states_.twist[robot_index_].angular.z;

        // calculate vector from nubot to football
        nubot_ball_vec_ = ball_state_.pose.position - robot_state_.pose.position;
        nubot_ball_vec_len_ = nubot_ball_vec_.GetLength();

        // transform kick_vector_nubot in world frame
        math::Quaternion    rotation_quaternion = robot_state_.pose.orient;
        math::Matrix3       RotationMatrix3 = rotation_quaternion.GetAsMatrix3();
        kick_vector_world_= RotationMatrix3 * kick_vector_robot; // vector from nubot origin to kicking mechanism in world frame
        // ROS_INFO("kick_vector_world_: %f %f %f",kick_vector_world_.x, kick_vector_world_.y, kick_vector_world_.z);

        obs_->world_obs_.reserve(20);
        obs_->real_obs_.reserve(20);
        obs_->world_obs_.clear();
        obs_->real_obs_.clear();
        omni_info_.robotinfo.reserve(10);
        omni_info_.robotinfo.clear();
        for(int i=0; i<model_count_;i++)
        {
            // Obstacles info (including teamates and opponent robots)
            if(model_states_.name[i].compare(0, cyan_pre_.size(), cyan_pre_) == 0 ||
               model_states_.name[i].compare(0, mag_pre_.size(), mag_pre_) == 0)   //compare model name' prefix to determine robots
            {
                math::Vector3 obs_pos(model_states_.pose[i].position.x, model_states_.pose[i].position.y, model_states_.pose[i].position.z);
                if(i != robot_index_)
                {
                    obs_->world_obs_.push_back(nubot::DPoint(obs_pos.x, obs_pos.y));

                    math::Vector3 nubot_obs_vec = obs_pos - robot_state_.pose.position;   // vector from nubot to obstacle
                    obs_->real_obs_.push_back( nubot::PPoint( get_angle_PI(kick_vector_world_,nubot_obs_vec),nubot_obs_vec.GetLength()) );
                }
            }

            // Teammates info (including myself)
            std::string team_pre = flip_cord_? mag_pre_ : cyan_pre_;
            if(model_states_.name[i].compare(0, team_pre.size(), team_pre) == 0)
            {
                int robot_id = atoi( model_states_.name[i].substr(team_pre.size(),1).c_str() );

                // get my own and teammates's info
                geometry_msgs::Pose  robot_pose = model_states_.pose[i];
                geometry_msgs::Twist robot_twist = model_states_.twist[i];
                math::Quaternion rot_qua(robot_pose.orientation.w, robot_pose.orientation.x,
                                         robot_pose.orientation.y, robot_pose.orientation.z);
                double heading_theta = rot_qua.GetYaw();
                teamate_info_.header.seq++;
                teamate_info_.header.stamp = ros::Time::now();
                teamate_info_.AgentID       = robot_id;
                teamate_info_.pos.x         = robot_pose.position.x * M2CM_CONVERSION;
                teamate_info_.pos.y         = robot_pose.position.y * M2CM_CONVERSION;
                teamate_info_.heading.theta = heading_theta;
                teamate_info_.vrot          = robot_twist.angular.z;
                teamate_info_.vtrans.x      = robot_twist.linear.x * M2CM_CONVERSION;
                //teamate_info_.isvalid       = true;
                teamate_info_.isvalid       =  is_robot_valid(robot_pose.position.x, robot_pose.position.y);
                teamate_info_.vtrans.y      = robot_twist.linear.y * M2CM_CONVERSION;
                teamate_info_.isstuck       = get_nubot_stuck();
                omni_info_.robotinfo.push_back(teamate_info_);
            }
        }

        return 1;
    }
    else
    {
        ROS_INFO("%s update_model_info(): Waiting for model_states messages!", model_name_.c_str());
        return 0;
    }
}

double NubotGazebo::noise(double scale, double probability)
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

void NubotGazebo::message_publish(void)
{
    //ros::Time simulation_time(receive_sim_time_.sec, receive_sim_time_.nsec);
    //math::Quaternion    rotation_quaternion=nubot_state_.pose.orientation;

    ////////////// OminiVision message /////////////////////////
    // ROS_INFO("Gazebo is publishing Omnivision Info!");
    ball_info_.header.stamp = ros::Time::now();
    ball_info_.header.seq++;
    ball_info_.ballinfostate = SEEBALLBYOWN;
    ball_info_.pos.x =  ball_state_.pose.position.x * M2CM_CONVERSION;
    ball_info_.pos.y =  ball_state_.pose.position.y * M2CM_CONVERSION;
    ball_info_.real_pos.angle  = get_angle_PI(kick_vector_world_,nubot_ball_vec_);
    ball_info_.real_pos.radius = nubot_ball_vec_len_ * M2CM_CONVERSION;
    ball_info_.velocity.x = ball_state_.twist.linear.x * M2CM_CONVERSION;
    ball_info_.velocity.y = ball_state_.twist.linear.y * M2CM_CONVERSION;
    ball_info_.pos_known = true;
    ball_info_.velocity_known = true;

    obstacles_info_.header.stamp = ros::Time::now();
    obstacles_info_.header.seq++;
    obstacles_info_.pos.clear();
    obstacles_info_.polar_pos.clear();
    int length= obs_->real_obs_.size();

    nubot_common::Point2d point;                                    // message type in ObstaclesInfo.msg
    nubot_common::PPoint  polar_point;                              // message type in ObstaclesInfo.msg
    for(int i = 0 ; i < length ; i++)
    {
        nubot::DPoint & pt=obs_->world_obs_[i];         // DPoint is a type in nubot/core/core.hpp
        nubot::PPoint & polar_pt= obs_->real_obs_[i];   // PPoint is a type in nubot/core/core.hpp

        point.x=pt.x_ * M2CM_CONVERSION ;                           // Get the location info and put it in message type
        point.y=pt.y_ * M2CM_CONVERSION;
        polar_point.angle=polar_pt.angle_.radian_;
        polar_point.radius=polar_pt.radius_;

        obstacles_info_.pos.push_back(point);
        obstacles_info_.polar_pos.push_back(polar_point);
    }
    omni_info_.header.stamp = ros::Time::now();
    omni_info_.header.seq++;
    omni_info_.ballinfo=ball_info_;
    omni_info_.obstacleinfo=obstacles_info_;
    omin_vision_pub_.publish(omni_info_);

}

void NubotGazebo::nubot_locomotion(math::Vector3 linear_vel_vector, math::Vector3 angular_vel_vector)
{
    desired_trans_vector_ = linear_vel_vector;
    desired_rot_vector_   = angular_vel_vector;
    // planar movement
    desired_trans_vector_.z = 0;
    desired_rot_vector_.x = 0;
    desired_rot_vector_.y = 0;
    robot_model_->SetLinearVel(desired_trans_vector_);
    robot_model_->SetAngularVel(desired_rot_vector_);
    judge_nubot_stuck_ = 1;                                                 // only afetr nubot tends to move can I judge if it is stuck
}

void NubotGazebo::vel_cmd_CB(const nubot_common::VelCmd::ConstPtr& cmd)
{
    msgCB_lock_.lock();

    if(flip_cord_)
    {
        Vx_cmd_ = -cmd->Vx * CM2M_CONVERSION;
        Vy_cmd_ = -cmd->Vy * CM2M_CONVERSION;
    }
    else
    {
        Vx_cmd_ = cmd->Vx * CM2M_CONVERSION;
        Vy_cmd_ = cmd->Vy * CM2M_CONVERSION;
    }
    w_cmd_  = cmd->w;
    math::Vector3 Vx_nubot = Vx_cmd_ * kick_vector_world_;
    math::Vector3 Vy_nubot = Vy_cmd_ * (math::Vector3(0,0,1).Cross(kick_vector_world_));    // velocity with reference to nubot
    math::Vector3 linear_vector = Vx_nubot + Vy_nubot;
    math::Vector3 angular_vector(0,0,w_cmd_);

    //    ROS_FATAL("%s vel_cmd_CB():linear_vector:%f %f %f angular_vector:0 0 %f",model_name_.c_str(),
    //                    linear_vector.x, linear_vector.y, linear_vector.z, angular_vector.z);
    nubot_locomotion(linear_vector, angular_vector);

    msgCB_lock_.unlock();
}

void NubotGazebo::obs_position(const nubot_common::Pos2d::ConstPtr &obs_pos)
{
    msgCB_lock_.lock();
    math::Pose obs_position(math::Vector3(obs_pos->pos.x*CM2M_CONVERSION, obs_pos->pos.y*CM2M_CONVERSION,0), math::Quaternion(0,0,0) );
    robot_model_->SetWorldPose(obs_position);
    msgCB_lock_.unlock();
}

bool NubotGazebo::ball_handle_control_service(nubot_common::BallHandle::Request  &req,
                                              nubot_common::BallHandle::Response &res)
{
    srvCB_lock_.lock();

    dribble_flag_ = req.enable ? 1 : 0;         // FIXME. when robot is stucked, req.enable=2
    if(dribble_flag_)
    {
        if(!get_is_hold_ball())     // when dribble_flag is true, it does not necessarily mean that I can dribble it now.
        {                           // it just means the dribble ball mechanism is working.
            dribble_flag_ = false;
            res.BallIsHolding = false;
            //ROS_INFO("dribble_service: Cannot dribble ball.");
        }
        else
        {
            //ROS_INFO("dribble_service: dribbling ball now");
            dribble_flag_  = true;
            res.BallIsHolding = true;
        }
    }
    else
    {
        res.BallIsHolding = get_is_hold_ball();
    }

    // ROS_FATAL("%s dribble:[enable holding]:[%d %d]",model_name_.c_str(), (int)req.enable, (int)res.BallIsHolding);
    srvCB_lock_.unlock();
    return true;
}

bool NubotGazebo::shoot_control_servive( nubot_common::Shoot::Request  &req,
                                         nubot_common::Shoot::Response &res )
{
    srvCB_lock_.lock();

    force_ = (double)req.strength;
    mode_ = (int)req.ShootPos;
    if(force_ > 15.0)
    {
        //ROS_FATAL("Kick ball force(%f) is too great.", force_);
        force_ = 15.0;
    }
    if( force_ )
    {
        if(get_is_hold_ball())
        {
            dribble_flag_ = false;
            shot_flag_ = true;
            //ROS_INFO("%s shoot_service: ShootPos:%d strength:%f",model_name_.c_str(), mode_, force_);
            res.ShootIsDone = 1;
        }
        else
        {
            shot_flag_ = false;
            res.ShootIsDone = 0;
            //ROS_INFO("%s shoot_service(): Cannot kick ball. angle error:%f distance error: %f. ",
            //                            model_name_.c_str(), angle_error_degree_, nubot_football_vector_length_);
        }
    }
    else
    {
        shot_flag_ = false;
        res.ShootIsDone = 1;
        //ROS_ERROR("%s shoot_control_service(): Kick-mechanism charging complete!",model_name_.c_str());
    }

    //ROS_INFO("%s shoot: [strength pos shootisdone]:[%f %d %d]",
    //            model_name_.c_str(), force_, mode_, (int)res.ShootIsDone);

    srvCB_lock_.unlock();
    return true;
}

void NubotGazebo::dribble_ball(void)
{

#if 1
    math::Quaternion    target_rot = robot_state_.pose.orient;
    math::Vector3       relative_pos = kick_vector_world_* 0.43;
    math::Vector3       target_pos;
    if(flip_cord_)
        target_pos = -(robot_state_.pose.position + relative_pos);
    else
        target_pos = robot_state_.pose.position + relative_pos;

    target_pos.z = 0.12;
    //ROS_INFO("target pos:%f %f %f",target_pos.x, target_pos.y, target_pos.z);
    math::Pose  target_pose(target_pos, target_rot);
    ball_model_->SetLinearVel(math::Vector3(0,0,0));
    ball_model_->SetWorldPose(target_pose);
    ball_state_.twist.linear = robot_state_.twist.linear;
#endif
#if 0
    const static double desired_nubot_football_vector_length =  dribble_distance_thres_;
    if(ball_state_.pose.position.z > 0.3)   // if football is in the air, cannot dribble
    {
        ROS_ERROR("dribble_ball(): ball is in the air at %f; return!", ball_state_.pose.position.z);
        return;
    }

    math::Vector3     nubot_linear_vel = nubot_model_->GetWorldLinearVel();
    math::Vector3     nubot_angular_vel = nubot_model_->GetWorldAngularVel();
    nubot_linear_vel.z=0; nubot_angular_vel.x=0; nubot_angular_vel.y=0;
    // Set up the direction from nubot to football. Let vector lies in x-y plane
    nubot_football_vector_.z = 0;                             // don't point to the air
    math::Vector3     perpencular_vel = nubot_angular_vel.Cross(nubot_football_vector_);
    math::Vector3     football_vel = nubot_linear_vel + perpencular_vel;
    football_model_->SetLinearVel(football_vel);

    ROS_INFO("%s dribble_ball(): dribbling ball. ball vel:%f %f", model_name_.c_str(),football_vel.x, football_vel.y);
#endif
}

void NubotGazebo::kick_ball(int mode, double vel=20.0)
{
    math::Vector3 kick_vector_planar(kick_vector_world_.x, kick_vector_world_.y, 0.0);
    math::Vector3 vel_vector;

    if(mode == RUN)
    {
        double vel2 = vel * 2.3;;                         //FIXME. CAN TUNE
        if(flip_cord_)
            vel_vector = -kick_vector_planar * vel2;
        else
            vel_vector = kick_vector_planar * vel2;

        ball_model_->SetLinearVel(vel_vector);
        ROS_INFO("kick ball vel:%f vel2:%f",vel, vel2);
    }
    else if(mode == FLY)
    {
        // math formular: y = a*x^2 + b*x + c;
        //  a = -g/(2*vx*vx), c = 0, b = kick_goal_height/D + g*D/(2.0*vx*vx)
        //  mid_point coordinates:[-b/(2*a), (4a*c-b^2)/(4a) ]

        static const double g = 9.8, kick_goal_height = goal_height - 0.20;      // FIXME: can be tuned
        nubot::DPoint point1(robot_state_.pose.position.x,robot_state_.pose.position.y);
        nubot::DPoint point2(robot_state_.pose.position.x + kick_vector_world_.x,
                             robot_state_.pose.position.y + kick_vector_world_.y);
        nubot::DPoint point3(ball_state_.pose.position.x,ball_state_.pose.position.y);
        nubot::Line_ line1(point1, point2);
        nubot::Line_ line2(1.0, 0.0, kick_vector_world_.x>0 ? -goal_x : goal_x);         // nubot::Line_(A,B,C);

        nubot::DPoint crosspoint = line1.crosspoint(line2);
        double D = crosspoint.distance(point3);
        double vx_thres = D*sqrt(g/2/kick_goal_height);
        double vx = vx_thres/2.0;//>vel ? vel : vx_thres/2.0;                            // initial x velocity.CAN BE TUNED
        double b = kick_goal_height/D + g*D/(2.0*vx*vx);

        ROS_INFO("%s crosspoint:(%f %f) vx: %f", model_name_.c_str(),
                 crosspoint.x_, crosspoint.y_, vx);
        if( fabs(crosspoint.y_) < 10)
        {
            math::Vector3 kick_vector;
            if(flip_cord_)
                kick_vector = math::Vector3(-vx*kick_vector_world_.x, -vx*kick_vector_world_.y, b*vx);
            else
                kick_vector = math::Vector3(vx*kick_vector_world_.x, vx*kick_vector_world_.y, b*vx);
            ball_model_->SetLinearVel(kick_vector);
        }
        else
            ROS_FATAL("CANNOT SHOOT. crosspoint.y is too big!");
    }
    else
    {
        ROS_ERROR("%s kick_ball(): Incorrect mode!", model_name_.c_str());
    }
}

bool NubotGazebo::get_is_hold_ball(void)
{
    bool near_ball, allign_ball;
    math::Vector3 norm = nubot_ball_vec_;
    norm.z=0.0; norm.Normalize();
    kick_vector_world_.z=0.0;
    angle_error_degree_ = get_angle_PI(kick_vector_world_,norm)*(180/PI);

    allign_ball = (angle_error_degree_ <= dribble_angle_thres_/2.0 && angle_error_degree_ >= -dribble_angle_thres_/2.0)?  1 : 0;
    near_ball = nubot_ball_vec_len_ <= dribble_distance_thres_? 1 : 0;

    return (near_ball && allign_ball);
}

bool NubotGazebo::get_nubot_stuck(void)
{
    static int time_count=0;
    static bool last_time_stuck=0;
    static const int time_limit = 40;
    static bool is_stuck;

    if(judge_nubot_stuck_)
    {
        judge_nubot_stuck_ = 0;
        static const double scale = 0.5;                                    // FIXME. Can tune
        double desired_trans_length = desired_trans_vector_.GetLength();
        double desired_rot_length   = desired_rot_vector_.z>0 ?
                    desired_rot_vector_.z :-desired_rot_vector_.z ;
        double actual_trans_length  = robot_state_.twist.linear.GetLength();
        double actual_rot_length    = robot_state_.twist.angular.z>0 ?
                    robot_state_.twist.angular.z : -robot_state_.twist.angular.z;

        //ROS_INFO("%s time_count:%d, last_time_stuck:%d",model_name_.c_str(), time_count, last_time_stuck);
        //ROS_INFO("desired_trans_len:%f actual_trans_len:%f",desired_trans_length,actual_trans_length);
        //ROS_INFO("desired_rot_len:%f actual_rot_len:%f",desired_rot_length, actual_rot_length);

        if(actual_trans_length < desired_trans_length * scale)
        {
            if(last_time_stuck)
                time_count++;
            else
                time_count = 0;

            last_time_stuck = 1;
            if(time_count > time_limit)
            {
                // ROS_INFO("get_nubot_stuck(): desired_trans:%f actual_trans:%f", desired_trans_length, actual_trans_length);
                // ROS_INFO("%s get_nubot_stuck(): cannot translate!", model_name_.c_str());
                time_count = 0;
                is_stuck = 1;
            }
        }
        else if(actual_rot_length < desired_rot_length * scale)
        {
            if(last_time_stuck)
                time_count++;
            else
                time_count = 0;

            last_time_stuck = 1;
            if(time_count > time_limit)
            {
                // ROS_INFO("desired_rot:%f actual_rot:%f", desired_rot_length, actual_rot_length);
                // ROS_ERROR("%s get_nubot_stuck(): cannot rotate!", model_name_.c_str());
                time_count = 0;
                is_stuck = 1;
            }
        }
        else
        {
            last_time_stuck = 0;
            is_stuck = 0;
        }

        return is_stuck;
    }
    else
    {
        //ROS_FATAL("%s judge_nubot_stuck_flag not set!", model_name_.c_str());
        return 0;
    }
}

void NubotGazebo::update_child()
{
    msgCB_lock_.lock(); // lock access to fields that are used in ROS message callbacks
    srvCB_lock_.lock();
    /* delay in model_states messages publishing
     * so after receiving model_states message, then nubot moves. */
    if(update_model_info())
    {
        /********** EDIT BEGINS **********/

        nubot_be_control();
        // nubot_test();

        /**********  EDIT ENDS  **********/
    }
    srvCB_lock_.unlock();
    msgCB_lock_.unlock();
}

void NubotGazebo::nubot_be_control(void)
{
    static int count=0;
    if(robot_state_.pose.position.z < 0.2)      // not in the air
    {
        //if(dribble_flag_)                       // dribble_flag_ is set by BallHandle service
        //{
        //    if(get_is_hold_ball())
        //        dribble_ball();
        //    else
        //        dribble_flag_ = false;
        //}

        if(dribble_flag_ && get_is_hold_ball())                       // dribble_flag_ is set by BallHandle service
            dribble_ball();

        if(shot_flag_)
        {
            kick_ball(mode_, force_);
            shot_flag_ = false;
        }
    }
    else
        ROS_FATAL("%s in the air!",model_name_.c_str());

    message_publish();                          // publish message to world_model node
}

bool NubotGazebo::is_robot_valid(double x, double y)
{
    if(fabs(x) > 10 || fabs(y) > 7)
        return false;
    else
        return true;
}

void NubotGazebo::nubot_test(void)
{
    // dribble ball
#if 0
    nubot_locomotion(math::Vector3(5,0,0),math::Vector3(0,0,2);
            dribble_ball();
    ROS_INFO("nubot-football distance:%f",nubot_football_vector_length_);
#endif
    // kick ball
#if 0
    static bool flag=1;
    if(flag)
    {
        kick_ball(FLY, 20);
        flag = 0;
    }
#endif
    // get nubot stuck flag test
#if 0
    bool a=get_nubot_stuck();
    ROS_FATAL("%d",a);
    nubot_locomotion(math::Vector3(0,0,0),math::Vector3(0,0,1));
#endif
    //for testing velocity decay
#if 0
    static int count=0;
    math::Vector3 vel(3,0,0);
    if(count++<50)
    {
        football_model_->SetLinearVel(vel);
        nubot_model_->SetLinearVel(math::Vector3(2,0,0));
    }
    debug_msgs_.data.clear();
    double data0 = football_model_->GetWorldLinearVel().GetLength();
    debug_msgs_.data.push_back(data0);
    debug_pub_.publish(debug_msgs_);
#endif
    // for testing time duration
#if 0
    common::Time                last_update_time_;
    last_update_time_ = world_->GetSimTime();
    for(int i=0; i<50; i++)
    {
        kick_ball(goal0_pos, mode, force);
        ROS_INFO("%s is kicking ball!",model_name_.c_str());
    }
    common::Time current_time = world_->GetSimTime();
    double seconds_since_last_update = ( current_time - last_update_time_ ).Double();
    ROS_FATAL("kick time:%f",seconds_since_last_update);
#endif
#if 0
    double vel = nubot_model_->GetWorldLinearVel().GetLength();
    //double vel2 = nubot_state_.twist.linear.x;
    nubot_locomotion(math::Vector3(1,0,0),ZERO_VECTOR);
    //ROS_INFO("function:%f state:%f",vel,vel2);
    debug_msgs_.data.clear();
    debug_msgs_.data.push_back(vel);
    //debug_msgs_.data.push_back(vel2);
    debug_pub_.publish(debug_msgs_);
#endif
}

/// For reference
/*
 Rot(z, 180 degrees), then quaterion: [d a b c] ==> [-c b -a d]
        double d = model_states_.pose[nubot_index_].orientation.w;
        double a = model_states_.pose[nubot_index_].orientation.x;
        double b = model_states_.pose[nubot_index_].orientation.y;
        double c = model_states_.pose[nubot_index_].orientation.z;
        nubot_state_.pose.orientation.w = -c;
        nubot_state_.pose.orientation.x = b;
        nubot_state_.pose.orientation.y = -a;
        nubot_state_.pose.orientation.z = d;
*/
