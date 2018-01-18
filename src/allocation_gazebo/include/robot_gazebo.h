#ifndef ROBOT_GAZEBO_H
#define ROBOT_GAZEBO_H

#include"gazebo_info.h"

class Robot_Gazebo : public gazebo::ModelPlugin
{
private:

    physics::WorldPtr                     world_;                              //a pointer to the gazebo world.
    physics::ModelPtr                     robot_model_;                        //pointer to the robot model

    ros::NodeHandle*                      rosnode_;
    ros::Subscriber                       robot2gazebo_sub_;

    boost::thread                         message_callback_queue_thread_;      //thead object for the running callback Thread.
    boost::mutex                          msgCB_lock_;                         //a mutex to lock access to fields that are used in ROS message callbacks
    ros::CallbackQueue                    message_queue_;                      //custom Callback Queue

    allocation_common::robot2gazebo_info  robot2gazebo_info_;

    math::Vector3                         desired_rot_vector_;
    math::Vector3                         desired_trans_vector_;
    math::Vector3                         unitX_world_;
    math::Vector3                         unitY_world_;

    std::string                           model_name_;
    std::string                           robot_namespace_;

    double                                Vx_cmd_;
    double                                Vy_cmd_;
    double                                w_cmd_;

    double                                dribble_P_;
    double                                dribble_I_;
    double                                dribble_D_;
    double                                I_term_max_;                         // maximum I term
    double                                I_term_min_;                         // minimum I term

    int                                   robotID_;
    dynamic_reconfigure::Server<allocation_gazebo::Robot_GazeboConfig> *reconfigureServer_;

public:
    Robot_Gazebo();
    virtual ~Robot_Gazebo();

    void    robot2gazebo_CB(const allocation_common::robot2gazebo_info::ConstPtr& _msg);
    void    robot_locomotion(math::Vector3 linear_vel_vector, math::Vector3 angular_vel_vector);
    void    message_queue_thread();
    void    robot_control();
    void    config(allocation_gazebo::Robot_GazeboConfig &config, uint32_t level);    
protected:
    void    Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/);
    virtual void Reset();
};

#endif //! ROBOT_GAZEBO_H
