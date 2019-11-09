#include <topic_info.h>

Topic_Info::Topic_Info()
{
    ros::Time::init();
    nh_= boost::make_shared<ros::NodeHandle>();
    terminalinfo_publish_timer_ = nh_->createTimer(ros::Duration(0.05),&Topic_Info::publish,this);
    terminal2robot_pub_  = nh_->advertise<allocation_common::terminal2robot_info>("/control_terminal/terminal2robot_info",1);
    terminal2gazebo_pub_ = nh_->advertise<allocation_common::terminal2gazebo_info>("/control_terminal/terminal2gazebo_info",1);
    terminal2DQN_pub_    = nh_->advertise<allocation_common::terminal2DQN_info>("/control_terminal/terminal2DQN_info",1);

    terminal2robots_info.allocation_mode=ALLOCATION_STOP;

    for(int i=0;i<MAXNUM_AGENT;i++)
        allocation2terminal_sub_[i]=nh_->subscribe <allocation_common::allocation2terminal_info>
                ("Robot"+std::to_string(i)+"/task_allocation/allocation2terminal_info",10,boost::bind(&Topic_Info::update_allocation_info,this,_1,i));
}

Topic_Info::~Topic_Info()
{

}

/// \brief publish the terminal info
void Topic_Info::publish(const ros::TimerEvent &)
{
    //pub the terminal2robot_info every period, control the allocation mode
    terminal2robot_pub_info_.allocation_mode=terminal2robots_info.allocation_mode;
    terminal2robot_pub_info_.greedorprobability=terminal2robots_info.greedorprobability;
    terminal2robot_pub_info_.allocation_method=terminal2robots_info.allocation_method;

    terminal2robot_pub_.publish(terminal2robot_pub_info_);

    //only publish when initialize a new allocation
    if(terminal2gazebo_info.isNew_allocation)
    {
        //pub the terminal2gazebo_info, the world will spawn the robots and tasks
        allocation_common::terminal2gazebo_info tmp_gazebo_info;
        for(int i=0;i<terminal2gazebo_info.task_pos_x.size();i++)
        {
            tmp_gazebo_info.task_pos_x.push_back(terminal2gazebo_info.task_pos_x[i]);
            tmp_gazebo_info.task_pos_y.push_back(terminal2gazebo_info.task_pos_y[i]);
        }
        for(int i=0;i<terminal2gazebo_info.robot_pos_x.size();i++)
        {
            tmp_gazebo_info.robot_pos_x.push_back(terminal2gazebo_info.robot_pos_x[i]);
            tmp_gazebo_info.robot_pos_y.push_back(terminal2gazebo_info.robot_pos_y[i]);
        }
        terminal2robot_pub_info_.all_allocation_robot_info.resize(terminal2gazebo_info.robot_pos_x.size());
        terminal2robot_pub_info_.all_allocation_task_info.resize(terminal2gazebo_info.task_pos_x.size());
        terminal2robots_info.all_allocation_robot_info.resize(terminal2gazebo_info.robot_pos_x.size());
        terminal2robots_info.all_allocation_task_info.resize(terminal2gazebo_info.task_pos_x.size());

        timeforupdaterobot_.resize(terminal2gazebo_info.robot_pos_x.size(),0);
        timeforupdatetask_.resize(terminal2gazebo_info.task_pos_x.size(),0);

        tmp_gazebo_info.is_noise=terminal2gazebo_info.is_noise;
        terminal2gazebo_info.isNew_allocation=false;
        terminal2gazebo_pub_.publish(tmp_gazebo_info);

        //pub the terminal2DQN_info, the DQN train will initialize
        allocation_common::terminal2DQN_info tmp_DQN_info;
//        for(int i=0;i<terminal2gazebo_info.task_pos_x.size();i++)
//        {
//            tmp_DQN_info.task_pos_x.push_back(terminal2gazebo_info.task_pos_x[i]);
//            tmp_DQN_info.task_pos_y.push_back(terminal2gazebo_info.task_pos_y[i]);
//        }
//        for(int i=0;i<terminal2gazebo_info.robot_pos_x.size();i++)
//        {
//            tmp_DQN_info.robot_pos_x.push_back(terminal2gazebo_info.robot_pos_x[i]);
//            tmp_DQN_info.robot_pos_y.push_back(terminal2gazebo_info.robot_pos_y[i]);
//        }
        tmp_DQN_info.task_number=terminal2gazebo_info.task_pos_x.size();
        tmp_DQN_info.team_number=terminal2gazebo_info.robot_pos_x.size();
        terminal2DQN_pub_.publish(tmp_DQN_info);
    }

    //only publish when finish the train using DQN method
    if((terminal2robots_info.finish_train||terminal2robots_info.finish_episode)&&terminal2robots_info.allocation_method==DQN)
    {
        allocation_common::terminal2DQN_info tmp_DQN_info;
//        for(int i=0;i<terminal2gazebo_info.task_pos_x.size();i++)
//        {
//            tmp_DQN_info.task_pos_x.push_back(terminal2gazebo_info.task_pos_x[i]);
//            tmp_DQN_info.task_pos_y.push_back(terminal2gazebo_info.task_pos_y[i]);
//        }
//        for(int i=0;i<terminal2gazebo_info.robot_pos_x.size();i++)
//        {
//            tmp_DQN_info.robot_pos_x.push_back(terminal2gazebo_info.robot_pos_x[i]);
//            tmp_DQN_info.robot_pos_y.push_back(terminal2gazebo_info.robot_pos_y[i]);
//        }
        tmp_DQN_info.task_number=terminal2gazebo_info.task_pos_x.size();
        tmp_DQN_info.team_number=terminal2gazebo_info.robot_pos_x.size();
        tmp_DQN_info.finish_episode=terminal2robots_info.finish_episode;
        tmp_DQN_info.finish_train=terminal2robots_info.finish_train;

        terminal2DQN_pub_.publish(tmp_DQN_info);

        terminal2robots_info.finish_episode=false;
        terminal2robots_info.finish_train=false;
    }

    //the info from allocation node will keep for two period
    for(unsigned i=0;i<terminal2robot_pub_info_.all_allocation_robot_info.size();i++)
        if(terminal2robot_pub_info_.all_allocation_robot_info[i].isupdate==true)
        {
            if(timeforupdaterobot_[i]==2)
                terminal2robot_pub_info_.all_allocation_robot_info[i].isupdate=false;
            else
                timeforupdaterobot_[i]++;
        }
    for(unsigned i=0;i<terminal2robot_pub_info_.all_allocation_task_info.size();i++)
        if(terminal2robot_pub_info_.all_allocation_task_info[i].isupdate==true)
        {
            if(timeforupdatetask_[i]==2)
                terminal2robot_pub_info_.all_allocation_task_info[i].isupdate=false;
            else
                timeforupdatetask_[i]++;
        }

    //when the allocation is stop, some parameter will reset
    if(terminal2robots_info.allocation_mode==ALLOCATION_STOP&&terminal2robots_info.all_allocation_robot_info.size()!=0
       &&terminal2robots_info.all_allocation_robot_info[0].move_distance!=0)
    {
        terminal2robot_pub_info_.all_allocation_robot_info.clear();
        terminal2robot_pub_info_.all_allocation_task_info.clear();
        terminal2robot_pub_info_.all_allocation_robot_info.resize(terminal2gazebo_info.robot_pos_x.size());
        terminal2robot_pub_info_.all_allocation_task_info.resize(terminal2gazebo_info.task_pos_x.size());

        for(unsigned int i=0;i<terminal2robots_info.all_allocation_robot_info.size();i++)
            terminal2robots_info.all_allocation_robot_info[i].robot_reset();
        for(unsigned int j=0;j<terminal2robots_info.all_allocation_task_info.size();j++)
            terminal2robots_info.all_allocation_task_info[j].task_reset();
    }
}
void
Topic_Info::run()
{
    ros::spin();
}

/// \brief each robot publish its allocation_info to the terminal node, and the terminal node put them in one message, then publish to the robots
void Topic_Info::update_allocation_info(const allocation_common::allocation2terminal_info::ConstPtr & _msg, int topic_id)
{
    //update for control terminal show
    terminal2robots_info.all_allocation_robot_info[topic_id].isvalid=_msg->robot_info.isvalid;
    terminal2robots_info.all_allocation_robot_info[topic_id].robot_ID=_msg->robot_info.robot_ID;
    terminal2robots_info.all_allocation_robot_info[topic_id].robot_mode=_msg->robot_info.robot_mode;
    terminal2robots_info.all_allocation_robot_info[topic_id].which_target=_msg->robot_info.which_target;
    terminal2robots_info.all_allocation_robot_info[topic_id].which_task=_msg->robot_info.which_task;
//    terminal2robots_info.all_allocation_robot_info[topic_id].expect_pos.x_=_msg->robot_info.expect_pos.position.x;
//    terminal2robots_info.all_allocation_robot_info[topic_id].expect_pos.y_=_msg->robot_info.expect_pos.position.y;
    terminal2robots_info.all_allocation_robot_info[topic_id].move_distance=_msg->robot_info.move_distance;

    if(_msg->task_info.task_ID!=-1)
    {
        int _task_id=_msg->task_info.task_ID;
        terminal2robots_info.all_allocation_task_info[_task_id].task_ID=_msg->task_info.task_ID;
        terminal2robots_info.all_allocation_task_info[_task_id].current_distance=_msg->task_info.current_distance;
        terminal2robots_info.all_allocation_task_info[_task_id].isallocated=_msg->task_info.isallocated;

        if(_msg->task_info.iscomplete)
            terminal2robots_info.all_allocation_task_info[_task_id].iscomplete=_msg->task_info.iscomplete;
        if(_msg->task_info.isexplored)
            terminal2robots_info.all_allocation_task_info[_task_id].isexplored=_msg->task_info.isexplored;
        if(_msg->task_info.istarget)
            terminal2robots_info.all_allocation_task_info[_task_id].istarget=_msg->task_info.istarget;
        if(terminal2robots_info.all_allocation_task_info[_task_id].known_power<_msg->task_info.known_power)
            terminal2robots_info.all_allocation_task_info[_task_id].known_power=_msg->task_info.known_power;
    }

    //update for pub to robot
    allocation_common::allocation_robot_info _tmp_robot_info;
    allocation_common::allocation_task_info  _tmp_task_info;

    _tmp_robot_info.isvalid=_msg->robot_info.isvalid;
    _tmp_robot_info.robot_ID=_msg->robot_info.robot_ID;
    _tmp_robot_info.robot_mode=_msg->robot_info.robot_mode;
    _tmp_robot_info.which_target=_msg->robot_info.which_target;
    _tmp_robot_info.which_task=_msg->robot_info.which_task;
    _tmp_robot_info.expect_pos.position.x=_msg->robot_info.expect_pos.position.x;
    _tmp_robot_info.expect_pos.position.y=_msg->robot_info.expect_pos.position.y;
    _tmp_robot_info.isupdate=true;
    timeforupdaterobot_[_tmp_robot_info.robot_ID]=0;

    //the robot_power is certained by control_terminal, not task_allocation
    _tmp_robot_info.robot_power=terminal2robots_info.all_allocation_robot_info[_tmp_robot_info.robot_ID].robot_power;
    terminal2robot_pub_info_.all_allocation_robot_info[topic_id]=_tmp_robot_info;
//    std::cout<<_tmp_robot_info.robot_ID<<" "<<topic_id<<std::endl;

    if(_msg->task_info.task_ID!=-1)
    {
        _tmp_task_info=terminal2robot_pub_info_.all_allocation_task_info[_msg->task_info.task_ID];

        _tmp_task_info.task_ID=_msg->task_info.task_ID;
        _tmp_task_info.isupdate=true;
        _tmp_task_info.current_distance=_msg->task_info.current_distance;
        _tmp_task_info.isallocated=_msg->task_info.isallocated;

        if(_msg->task_info.iscomplete)
            _tmp_task_info.iscomplete=_msg->task_info.iscomplete;
        if(_msg->task_info.isexplored)
            _tmp_task_info.isexplored=_msg->task_info.isexplored;
        if(_msg->task_info.istarget)
            _tmp_task_info.istarget=_msg->task_info.istarget;
        if(_tmp_task_info.known_power<_msg->task_info.known_power)
            _tmp_task_info.known_power=_msg->task_info.known_power;

        //the task_power is certained by control_terminal, not task_allocation
        _tmp_task_info.task_power=terminal2robots_info.all_allocation_task_info[_tmp_task_info.task_ID].task_power;
        terminal2robot_pub_info_.all_allocation_task_info[_tmp_task_info.task_ID]=_tmp_task_info;
        timeforupdatetask_[_tmp_task_info.task_ID]=0;
    }
}
