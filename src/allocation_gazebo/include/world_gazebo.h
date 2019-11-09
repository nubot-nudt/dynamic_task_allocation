#ifndef WORLD_GAZEBO_H
#define WORLD_GAZEBO_H

#include "gazebo_info.h"

class World_Gazebo : public gazebo::WorldPlugin
{
private:

    physics::WorldPtr                       world_;                              //a pointer to the gazebo world.
    std::string                             world_name_;                         //the allocation_map name

    transport::NodePtr                      node_;                               //Create a new transport node
    transport::PublisherPtr                 factoryPub_;                         //Create a publisher on the ~/factory topic
    ros::NodeHandle*                        rosnode_;
    ros::Subscriber                         ModelStates_sub_;                    //scriber the all modelstates in the gazebo
    ros::Subscriber                         terminal2gazebo_sub_;                //scriber the terminal info
    ros::Publisher                          gazebo2world_pub_;                   //publish the gazebo world info
    ros::Publisher                          debug_pub_;                          //for debug

    boost::thread                           message_callback_queue_thread_;      //thead object for the running callback Thread.
    boost::mutex                            msgCB_lock_;                         //a mutex to lock access to fields that are used in ROS message callbacks
    ros::CallbackQueue                      message_queue_;                      //custom Callback Queue

    event::ConnectionPtr                    update_connection_;                  //pointer to the update event connection

    allocation_common::gazebo_robot_info    robots_info_;                        //the msg gazebo2world_info contain robots_info and tasks_info
    allocation_common::gazebo_task_info     tasks_info_;
    std_msgs::Float64MultiArray             debug_msgs_;

    ignition::math::Vector3d                unitX_robot_;
    ignition::math::Rand                    rand_;
    double                                  noise_scale_;                        //scale of gaussian noise
    double                                  noise_rate_;                         //how frequent the noise generates
    bool                                    ModelStatesCB_flag_;                 //the flag after ModelStates callback

    gazebo_msgs::ModelStates                model_states_;                       //the class about model state
    unsigned int                            model_count_;                        //the number of models

public:
    World_Gazebo();
    virtual ~World_Gazebo();

    void    model_states_CB(const gazebo_msgs::ModelStates::ConstPtr & _msg);
    void    terminal_info_CB(const allocation_common::terminal2gazebo_info::ConstPtr &_msg);
    void    message_queue_thread();
    bool    update_model_info(void);
    double  noise(double scale, double probability=0.01);

protected:
    void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf);
    virtual void update_child();
    virtual void Reset();
};

#endif //! WORLD_GAZEBO_H
