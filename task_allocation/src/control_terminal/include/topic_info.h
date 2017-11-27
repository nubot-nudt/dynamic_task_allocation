#ifndef TOPIC_INFO_H
#define TOPIC_INFO_H

#include <Core.hpp>
#include <QThread>
#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <std_msgs/String.h>
#include <common/terminal2gazebo_info.h>

class Topic_Info:public QThread
{
public:
    /**ros items**/
    boost::shared_ptr<ros::NodeHandle> nh_;
    ros::Subscriber  robot2terminal_sub_;
    ros::Publisher   terminal2robot_pub_;
    ros::Publisher   terminal2gazebo_pub_;
    ros::Timer       terminalinfo_publish_timer_;

    common::terminal2gazebo_info terminal2gazebo_pub_info_;

    Terminal2Robots_info terminal2robots_info;
    Terminal2Gazebo_info terminal2gazebo_info;

public:
    Topic_Info();
    void run();
//    void update_info(const nubot_common::WorldModelInfo & _world_msg);
    void publish(const ros::TimerEvent &);
    ~Topic_Info();
};

#endif // TOPIC_INFO_H
