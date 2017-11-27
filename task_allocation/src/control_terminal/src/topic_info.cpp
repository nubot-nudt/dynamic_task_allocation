#include <topic_info.h>

Topic_Info::Topic_Info()
{
    ros::Time::init();
    nh_= boost::make_shared<ros::NodeHandle>();
    terminalinfo_publish_timer_ = nh_->createTimer(ros::Duration(0.03),&Topic_Info::publish,this);
    //terminal2robot_pub_ = nh_->advertise<nubot_common::CoachInfo>("/control_terminal/terminal2robot_info",30);
    terminal2gazebo_pub_ = nh_->advertise<common::terminal2gazebo_info>("terminal2gazebo_info",1);
}

Topic_Info::~Topic_Info()
{
}

//publish the terminal info
void Topic_Info::publish(const ros::TimerEvent &)
{
    if(terminal2gazebo_info.ismap_recreate_)
    {
        //only publish one time when init_map is clicked
        terminal2gazebo_pub_info_.map_height_msg=terminal2gazebo_info.map_height_;
        terminal2gazebo_pub_info_.map_width_msg=terminal2gazebo_info.map_width_;
        terminal2gazebo_pub_info_.map_room_msg=terminal2gazebo_info.map_room_;
        terminal2gazebo_info.ismap_recreate_=false;

        terminal2gazebo_pub_.publish(terminal2gazebo_pub_info_);
    }
}
void
Topic_Info::run()
{
    ros::spin();
}
