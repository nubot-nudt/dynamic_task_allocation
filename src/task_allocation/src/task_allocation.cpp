#include "task_allocation.h"
//#define debug

Task_Allocation::Task_Allocation(int argc,char** argv)
{
    //robot_name="Robot i"
    std::string robot_name=argv[1];
    const char * robot_ID;
    robot_ID=robot_name.substr(robot_name.size()-1).c_str();
    my_robot_.allocation_robot_info.robot_ID=atoi(robot_ID);
    my_robot_.gazebo_robot_info.robot_ID=atoi(robot_ID);
    ROS_INFO("start %s task_allocation_process",robot_name.c_str());

    nh_ = new ros::NodeHandle();
    robot2gazebo_pub_       =nh_->advertise<allocation_common::robot2gazebo_info>(robot_name+"/task_allocation/robot2gazebo_info",10);
    //robot2task_pub_         =nh_->advertise<allocation_common::allocation_task_info>("/task_allocation/task_state_info",1);
    allocation2terminal_pub_=nh_->advertise<allocation_common::allocation2terminal_info>(robot_name+"/task_allocation/allocation2terminal_info",10);
    drawing_pub_            =nh_->advertise<geometry_msgs::Point>(robot_name+"/task_allocation/drawing_info",10);
    gazebo2world_sub_       =nh_->subscribe("/allocation_gazebo/gazebo2world_info",10,&Task_Allocation::update_gazebo_world,this);
    terminal2robot_sub_     =nh_->subscribe("/control_terminal/terminal2robot_info",10,&Task_Allocation::update_terminal_info,this);
    get_action_client_      =nh_->serviceClient<allocation_common::GetAction>("dqn_ros/get_action");
    return_reward_client_   =nh_->serviceClient<allocation_common::ReturnReward>("dqn_ros/return_reward");
    allocation_timer_       =nh_->createTimer(ros::Duration(0.05),&Task_Allocation::loopControl,this);
    f = boost::bind(&Task_Allocation::ParamChanged, this, _1, _2);
    server.setCallback(f);

    my_behaviour_=new Behaviour(obstacles_);

    num_task_valid_=1;
    num_target_valid_=0;
    num_task_unallocated_=1;
    num_target_unallocated_=0;
    bid_new_task_=false;
    bid_new_target_=false;
    is_target_completed=false;
    is_task_explored=false;
    is_world_update_=false;
    is_all_completed=false;
    all_tasks_.clear();
    all_robots_.clear();

    my_robot_.allocation_robot_info.isvalid=true;
}

Task_Allocation::~Task_Allocation()
{
    num_task_valid_=1;
    num_target_valid_=0;
    num_task_unallocated_=1;
    num_target_unallocated_=0;
    bid_new_task_=false;
    bid_new_target_=false;
    is_target_completed=false;
    is_task_explored=false;
    is_world_update_=false;
    is_all_completed=false;
}

/// \brief update the model sate from gazebo msg
void Task_Allocation::update_gazebo_world(const allocation_common::gazebo2world_info::ConstPtr &_msg)
{
    //because the robots' pos is change,clear the obstacles and re-push the pos of robots
    obstacles_.clear();
    //first callback, if all_robots is a null vector, resize its size according to the _msg from gazebo
    if(all_robots_.size()==0)
        all_robots_.resize(_msg->gazebo_robots_info.size());

    Gazebo_robot_info _robot_info_tmp;
    //update the gazebo robots states for allocation
    for(unsigned int i=0;i<_msg->gazebo_robots_info.size();i++)
    {
        _robot_info_tmp.robot_ID=_msg->gazebo_robots_info[i].robot_ID;
        _robot_info_tmp.robot_pos.x_=_msg->gazebo_robots_info[i].robot_pose.position.x;
        _robot_info_tmp.robot_pos.y_=_msg->gazebo_robots_info[i].robot_pose.position.y;
        _robot_info_tmp.robot_ori=_msg->gazebo_robots_info[i].robot_pose.theta;
        _robot_info_tmp.robot_vel.x_=_msg->gazebo_robots_info[i].robot_twist.linear.x;
        _robot_info_tmp.robot_vel.y_=_msg->gazebo_robots_info[i].robot_twist.linear.y;
        _robot_info_tmp.robot_w=_msg->gazebo_robots_info[i].robot_twist.angular;

        //update the robot model when it is valid
        if(all_robots_[_robot_info_tmp.robot_ID].allocation_robot_info.isvalid)
            all_robots_[_robot_info_tmp.robot_ID].gazebo_robot_info=_robot_info_tmp;

        //the robot is placed on the init position, the expect_pos is robot_pos and update robot_ID
        if(all_robots_[_robot_info_tmp.robot_ID].allocation_robot_info.expect_pos.x_==-100)
        {
            all_robots_[_robot_info_tmp.robot_ID].allocation_robot_info.robot_ID=_robot_info_tmp.robot_ID;
            all_robots_[_robot_info_tmp.robot_ID].allocation_robot_info.expect_pos=_robot_info_tmp.robot_pos;
        }

        //if the robot_ID is me
        if(_robot_info_tmp.robot_ID==my_robot_.gazebo_robot_info.robot_ID)
        {
            my_robot_.allocation_robot_info.move_distance=my_robot_.allocation_robot_info.move_distance+_robot_info_tmp.robot_pos.distance(my_robot_.gazebo_robot_info.robot_pos);
            my_robot_.gazebo_robot_info=_robot_info_tmp;
            if(my_robot_.allocation_robot_info.expect_pos.x_==-100)
                my_robot_.allocation_robot_info.expect_pos=_robot_info_tmp.robot_pos;
        }

        //if the robot_ID is not me, it is a obstacle
        else
            obstacles_.push_back(DPoint(_robot_info_tmp.robot_pos.x_,_robot_info_tmp.robot_pos.y_));
    }

    //first callback, if all_tasks is a null vector, resize its size according to the _msg from gazebo, and because the position of task will not change, the callback only be executed one time
    if(all_tasks_.size()==0)
    {
        all_tasks_.resize(_msg->gazebo_tasks_info.size());

        Gazebo_task_info  _task_info_tmp;
        //update the gazebo tasks states for allocation
        for(unsigned int j=0;j<_msg->gazebo_tasks_info.size();j++)
        {
            _task_info_tmp.task_ID=_msg->gazebo_tasks_info[j].task_ID;
            _task_info_tmp.task_pos.x_=_msg->gazebo_tasks_info[j].task_pose.x;
            _task_info_tmp.task_pos.y_=_msg->gazebo_tasks_info[j].task_pose.y;

            //update the task model when it is uncomplete
            if(!all_tasks_[_task_info_tmp.task_ID].allocation_task_info.iscomplete||!all_tasks_[_task_info_tmp.task_ID].allocation_task_info.isexplored)
                all_tasks_[_task_info_tmp.task_ID].gazebo_task_info=_task_info_tmp;

            all_tasks_[_task_info_tmp.task_ID].allocation_task_info.task_ID=_task_info_tmp.task_ID;
        }
    }
}

/// \brief update the terminal info to control the allocation process
void Task_Allocation::update_terminal_info(const allocation_common::terminal2robot_info::ConstPtr &_msg)
{
    //first callback, if all_robots is a null vector, wait the gazebo_msg to initilize the vector
    if(all_robots_.size()==0)
        return;

    terminal_info_.allocation_mode=_msg->allocation_mode;
    terminal_info_.greedorprobability=_msg->greedorprobability;
    terminal_info_.allocation_method=_msg->allocation_method;

    Allocation_robot_info _robot_info_tmp;
    //update the allocation_info of robots, exceput my_robot
    for(unsigned int i=0;i<_msg->all_allocation_robot_info.size();i++)
    {
        if(_msg->all_allocation_robot_info[i].isupdate)
        {
            if(_msg->all_allocation_robot_info[i].robot_ID!=my_robot_.allocation_robot_info.robot_ID)
            {
                _robot_info_tmp.robot_ID=_msg->all_allocation_robot_info[i].robot_ID;
                _robot_info_tmp.isvalid=_msg->all_allocation_robot_info[i].isvalid;
                _robot_info_tmp.robot_mode=_msg->all_allocation_robot_info[i].robot_mode;
                _robot_info_tmp.robot_power=_msg->all_allocation_robot_info[i].robot_power;
                _robot_info_tmp.which_target=_msg->all_allocation_robot_info[i].which_target;
                _robot_info_tmp.which_task=_msg->all_allocation_robot_info[i].which_task;
                _robot_info_tmp.expect_pos.x_=_msg->all_allocation_robot_info[i].expect_pos.position.x;
                _robot_info_tmp.expect_pos.y_=_msg->all_allocation_robot_info[i].expect_pos.position.y;

                all_robots_[_robot_info_tmp.robot_ID].allocation_robot_info=_robot_info_tmp;
            }
            else
            {
                //the robot_power is obtained from terminal, although the id is same, need to be update
                my_robot_.allocation_robot_info.robot_power=_msg->all_allocation_robot_info[i].robot_power;
                all_robots_[my_robot_.allocation_robot_info.robot_ID].allocation_robot_info=my_robot_.allocation_robot_info;
            }
        }
    }

    //first callback, if all_tasks is a null vector, wait the gazebo_msg to initilize the vector
    if(all_tasks_.size()==0)
        return;

    Allocation_task_info _task_info_tmp;
    int _num_task=0;
    int _num_target=0;
    //update the allocation_info of tasks
    for(unsigned int j=0;j<_msg->all_allocation_task_info.size();j++)
    {
        if(_msg->all_allocation_task_info[j].isupdate)
        {
            //obtain the current allocation_task_info, then the information will part update
            _task_info_tmp=all_tasks_[_msg->all_allocation_task_info[j].task_ID].allocation_task_info;
            if(terminal_info_.allocation_method==Prediction)
            {
                //the task/target has been allocated to me will not update these information
                if(_msg->all_allocation_task_info[j].task_ID!=my_robot_.allocation_robot_info.which_target&&
                   _msg->all_allocation_task_info[j].task_ID!=my_robot_.allocation_robot_info.which_task)
                {
                    _task_info_tmp.task_ID=_msg->all_allocation_task_info[j].task_ID;
                    _task_info_tmp.current_distance=_msg->all_allocation_task_info[j].current_distance;
                    _task_info_tmp.iscomplete=_msg->all_allocation_task_info[j].iscomplete;
                    _task_info_tmp.isexplored=_msg->all_allocation_task_info[j].isexplored;
                    _task_info_tmp.istarget=_msg->all_allocation_task_info[j].istarget;
                    _task_info_tmp.known_power=_msg->all_allocation_task_info[j].known_power;

                    //std::cout<<_task_info_tmp.isexplored<<std::endl;
                    all_tasks_[_task_info_tmp.task_ID].allocation_task_info=_task_info_tmp;
                }
                //the task/target has been allocated to me will update task_power
                else
                {
                    _task_info_tmp.task_ID=_msg->all_allocation_task_info[j].task_ID;
                    _task_info_tmp.task_power=_msg->all_allocation_task_info[j].task_power;
                    all_tasks_[_task_info_tmp.task_ID].allocation_task_info=_task_info_tmp;
                }
            }

            else if(terminal_info_.allocation_method==Market)
            {
                bool _isMytask=false;
                bool _isMytarget=false;

                for(unsigned int m=0;m<my_robot_.allocation_robot_info.task_list.size();m++)
                    if(_msg->all_allocation_task_info[j].task_ID==my_robot_.allocation_robot_info.task_list[m])
                    {
                        _isMytask=true;
                        break;
                    }
                for(unsigned int n=0;n<my_robot_.allocation_robot_info.target_list.size();n++)
                    if(_msg->all_allocation_task_info[j].task_ID==my_robot_.allocation_robot_info.target_list[n])
                    {
                        _isMytarget=true;
                        break;
                    }
                //the task/target has been allocated to me will update task_power
                if(_isMytarget||_isMytask)
                {
                    _task_info_tmp.task_ID=_msg->all_allocation_task_info[j].task_ID;
                    _task_info_tmp.task_power=_msg->all_allocation_task_info[j].task_power;
                    all_tasks_[_task_info_tmp.task_ID].allocation_task_info=_task_info_tmp;
                }
                //the tasks/targets have been allocated to me will not update these information
                else
                {
                    _task_info_tmp.task_ID=_msg->all_allocation_task_info[j].task_ID;
                    _task_info_tmp.iscomplete=_msg->all_allocation_task_info[j].iscomplete;
                    _task_info_tmp.isexplored=_msg->all_allocation_task_info[j].isexplored;
                    _task_info_tmp.isallocated=_msg->all_allocation_task_info[j].isallocated;
                    _task_info_tmp.istarget=_msg->all_allocation_task_info[j].istarget;
                    _task_info_tmp.known_power=_msg->all_allocation_task_info[j].known_power;

                    all_tasks_[_task_info_tmp.task_ID].allocation_task_info=_task_info_tmp;
                }
            }
            else
            {
                //only the false->true change is allowed, the true->false is invalid
                _task_info_tmp.task_ID=_msg->all_allocation_task_info[j].task_ID;
                if(_msg->all_allocation_task_info[j].iscomplete)
                    _task_info_tmp.iscomplete=_msg->all_allocation_task_info[j].iscomplete;
                if(_msg->all_allocation_task_info[j].isexplored)
                    _task_info_tmp.isexplored=_msg->all_allocation_task_info[j].isexplored;
                if(_msg->all_allocation_task_info[j].istarget)
                    _task_info_tmp.istarget=_msg->all_allocation_task_info[j].istarget;
                if(_task_info_tmp.known_power<_msg->all_allocation_task_info[j].known_power)
                    _task_info_tmp.known_power=_msg->all_allocation_task_info[j].known_power;

                _task_info_tmp.isallocated=_msg->all_allocation_task_info[j].isallocated;
                _task_info_tmp.task_power=_msg->all_allocation_task_info[j].task_power;
                all_tasks_[_task_info_tmp.task_ID].allocation_task_info=_task_info_tmp;
            }
        }
    }
    //record the uncomplete task and target
    for(unsigned int i=0;i<all_tasks_.size();i++)
    {
        if(!all_tasks_[i].allocation_task_info.iscomplete&&all_tasks_[i].allocation_task_info.istarget)
            _num_target++;
        else if(!all_tasks_[i].allocation_task_info.isexplored)
            _num_task++;
    }
    num_task_valid_=_num_task;
    num_target_valid_=_num_target;
    //for market_base method, the number of unallocated tasks/targets will also be recorded
    if(terminal_info_.allocation_method==Market)
    {
        _num_task=0;
        _num_target=0;
        for(unsigned int i=0;i<all_tasks_.size();i++)
            if(!all_tasks_[i].allocation_task_info.isallocated)
            {
                if(all_tasks_[i].allocation_task_info.istarget)
                    _num_target++;
                else
                    _num_task++;
            }
        num_task_unallocated_=_num_task;
        num_target_unallocated_=_num_target;
    }
}

/// \brief the process that robot to explore the task
bool Task_Allocation::try2explore_()
{
    static int _explore_time=0;
    Task_info _my_task;
    int _which_task;
    //the task which execute next is different between prediction and market
    if(terminal_info_.allocation_method==Prediction||terminal_info_.allocation_method==DQN)
        _which_task=my_robot_.allocation_robot_info.which_task;
    else
        _which_task=my_robot_.allocation_robot_info.task_list.front();
    _my_task=all_tasks_[_which_task];

    if(terminal_info_.allocation_method==Prediction||terminal_info_.allocation_method==DQN)
        for(unsigned int i=0;i<all_robots_.size();i++)
            //there is an other robot ready for this task except me
            if(all_robots_[i].allocation_robot_info.robot_ID!=my_robot_.allocation_robot_info.robot_ID
                    &&all_robots_[i].allocation_robot_info.which_task==my_robot_.allocation_robot_info.which_task
                    &&all_robots_[i].allocation_robot_info.isvalid)
            {
                int distance_1=my_robot_.gazebo_robot_info.robot_pos.distance(_my_task.gazebo_task_info.task_pos);
                int distance_2=all_robots_[i].gazebo_robot_info.robot_pos.distance(_my_task.gazebo_task_info.task_pos);
                //other robot's distance is littler
                if(distance_1>distance_2)
                {
                    //drop this task
                    my_robot_.allocation_robot_info.robot_mode=IDLE;
#ifdef debug
                    std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" drops task "<<my_robot_.allocation_robot_info.which_task<<" because of robot "<<i<<std::endl;
#endif
                    if(terminal_info_.allocation_method==DQN)
                        return_rewrad_(Drop_task);
                    return false;
                }
            }

    my_robot_.allocation_robot_info.robot_mode=EXECUTE;
    //there is no conflict, continue to carry out the task
    if(my_robot_.gazebo_robot_info.robot_pos.distance(_my_task.gazebo_task_info.task_pos)>LOCATION_ERROR)
    {
        float thetaofr2t = _my_task.gazebo_task_info.task_pos.angle(my_robot_.gazebo_robot_info.robot_pos).radian_;
        my_behaviour_->move2Positionwithobs(3,6,_my_task.gazebo_task_info.task_pos,4,my_robot_.gazebo_robot_info.robot_pos,my_robot_.gazebo_robot_info.robot_ori);
        all_tasks_[_which_task].allocation_task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(_my_task.gazebo_task_info.task_pos);
//        my_behaviour_->rotate2AbsOrienation(2,5,thetaofr2t,5,my_robot_.gazebo_robot_info.robot_ori);
        return false;
    }
    //if reach the task pos
    else
    {
        //explore the task
        my_robot_.allocation_robot_info.robot_mode=EXPLORE;
        if(_explore_time<EXPLORE_TIME)
        {
            _explore_time++;
            return false;
        }
        else
        {
            _explore_time=0;
            all_tasks_[_which_task].allocation_task_info.isexplored=true;
            //this is a target
            if(_my_task.allocation_task_info.task_power>0)
            {
                all_tasks_[_which_task].allocation_task_info.known_power=1;
                all_tasks_[_which_task].allocation_task_info.istarget=true;
                //allocate this target to this robot right now
                //if the target power bigger than the robot power, the robot will be destroyed
                if(_my_task.allocation_task_info.task_power>my_robot_.allocation_robot_info.robot_power)
                {
#ifdef debug
                    std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" is destroyed!"<<std::endl;
#endif
                    my_robot_.allocation_robot_info.robot_mode=DAMAGE;
                    my_robot_.allocation_robot_info.isvalid=false;
                    all_tasks_[_which_task].allocation_task_info.known_power=my_robot_.allocation_robot_info.robot_power+1;

                    if(terminal_info_.allocation_method==Prediction)
                        all_tasks_[_which_task].allocation_task_info.current_distance=1000;
                    else if(terminal_info_.allocation_method==Market)
                        all_tasks_[_which_task].allocation_task_info.isallocated=false;
                    else
                    {
                        all_tasks_[_which_task].allocation_task_info.isallocated=false;
                        return_rewrad_(Robot_damage);
                    }
                }
                //if the target power less than the robot power, the target will be destroyed
                else
                {
                    all_tasks_[_which_task].allocation_task_info.iscomplete=true;
                    if(terminal_info_.allocation_method==DQN)
                        return_rewrad_(Complete_target);
                }
            }
            else
            {
                all_tasks_[_which_task].allocation_task_info.iscomplete=true;
                if(terminal_info_.allocation_method==DQN)
                    return_rewrad_(Explore_task);
            }
            return true;
        }
    }
}

/// \brief  the process that robot to hit the target
bool Task_Allocation::try2hit_()
{
    static int _hit_time=0;
    Task_info _my_target;
    int _which_target;
    //the target which execute next is different between prediction, DQN and market
    if(terminal_info_.allocation_method==Prediction||terminal_info_.allocation_method==DQN)
        _which_target=my_robot_.allocation_robot_info.which_target;
    else
        _which_target=my_robot_.allocation_robot_info.target_list.front();
    _my_target=all_tasks_[_which_target];

    if(terminal_info_.allocation_method==Prediction||terminal_info_.allocation_method==DQN)
        for(unsigned int i=0;i<all_robots_.size();i++)
            //there is an other robot ready for this target except me
            if(all_robots_[i].allocation_robot_info.robot_ID!=my_robot_.allocation_robot_info.robot_ID
                    &&all_robots_[i].allocation_robot_info.which_target==my_robot_.allocation_robot_info.which_target
                    &&all_robots_[i].allocation_robot_info.isvalid)
            {
                int distance_1=my_robot_.gazebo_robot_info.robot_pos.distance(_my_target.gazebo_task_info.task_pos);
                int distance_2=all_robots_[i].gazebo_robot_info.robot_pos.distance(_my_target.gazebo_task_info.task_pos);
                //other robot's distance is littler
                if(distance_1>distance_2)
                {
                    //drop this target
                    my_robot_.allocation_robot_info.robot_mode=IDLE;
#ifdef debug
                    std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" drops target "<<my_robot_.allocation_robot_info.which_target<<" because of robot "<<i<<std::endl;
#endif
                    if(terminal_info_.allocation_method==DQN)
                        return_rewrad_(Drop_task);
                    return false;
                }
            }

    my_robot_.allocation_robot_info.robot_mode=EXECUTE;
    //there is no conflict, continue to carry out this target
    if(my_robot_.gazebo_robot_info.robot_pos.distance(_my_target.gazebo_task_info.task_pos)>LOCATION_ERROR)
    {
        float thetaofr2t = _my_target.gazebo_task_info.task_pos.angle(my_robot_.gazebo_robot_info.robot_pos).radian_;
        my_behaviour_->move2Positionwithobs(3,6,_my_target.gazebo_task_info.task_pos,4,my_robot_.gazebo_robot_info.robot_pos,my_robot_.gazebo_robot_info.robot_ori);
        all_tasks_[_which_target].allocation_task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(_my_target.gazebo_task_info.task_pos);
//        my_behaviour_->rotate2AbsOrienation(2,5,thetaofr2t,5,my_robot_.gazebo_robot_info.robot_ori);
        return false;
    }
    //reach the target position
    else
    {
        //if the target power bigger than the robot power, the robot will be destroyed
        if(_my_target.allocation_task_info.task_power>my_robot_.allocation_robot_info.robot_power)
        {
#ifdef debug
            std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" is destroyed!"<<std::endl;
#endif
            my_robot_.allocation_robot_info.robot_mode=DAMAGE;
            my_robot_.allocation_robot_info.isvalid=false;
            all_tasks_[_which_target].allocation_task_info.known_power=my_robot_.allocation_robot_info.robot_power+1;

            if(terminal_info_.allocation_method==Prediction)
                all_tasks_[_which_target].allocation_task_info.current_distance=1000;
            else if(terminal_info_.allocation_method==Market)
                all_tasks_[_which_target].allocation_task_info.isallocated=false;
            else
            {
                all_tasks_[_which_target].allocation_task_info.isallocated=false;
                return_rewrad_(Robot_damage);
            }

            return false;
        }
        //if the target power less than the robot power, the target will be destroyed
        else
        {
            //the target is complete
            my_robot_.allocation_robot_info.robot_mode=HIT;
            if(_hit_time<HIT_TIME)
            {
                _hit_time++;
                return false;
            }
            else
            {
                _hit_time=0;
                all_tasks_[_which_target].allocation_task_info.iscomplete=true;
                if(terminal_info_.allocation_method==DQN)
                    return_rewrad_(Complete_target);
                return true;
            }
        }
    }
}

/// \brief the robot choose the task (hit or explore)
bool Task_Allocation::choose2hitOrexplore_()
{
    //initialization the variable
    std::vector<double> distance_vec;
    std::vector<int> possible_vec;
    std::vector<int> power_vec;
    std::vector<int> lab_vec;
    float distance=0;
    int sum_possible=0;
    int _which_target=-1;
    int _which_task=-1;

    if(!num_target_valid_&&!num_task_valid_)
        return false;

    //there are targets which uncomplete
    if(num_target_valid_>0)
    {
        //make choice base on greed or probability
        if(!terminal_info_.greedorprobability)
        {
            float less_distance=1000;
            //calculate the distance between my_robot and each uncomplete target
            for(unsigned int i=0;i<all_tasks_.size();i++)
                if(all_tasks_[i].allocation_task_info.istarget==true&&all_tasks_[i].allocation_task_info.iscomplete==false
                   &&my_robot_.allocation_robot_info.robot_power>=all_tasks_[i].allocation_task_info.known_power
                   &&my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos)<all_tasks_[i].allocation_task_info.current_distance)
                {
                    distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos);
                    if(distance<less_distance)
                    {
                        less_distance=distance;
                        my_robot_.allocation_robot_info.which_target=all_tasks_[i].allocation_task_info.task_ID;
                    }
                }
            if(my_robot_.allocation_robot_info.which_target!=-1)
            {
                my_robot_.allocation_robot_info.robot_mode=PLAN;
                _which_target=my_robot_.allocation_robot_info.which_target;
                all_tasks_[_which_target].allocation_task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[_which_target].gazebo_task_info.task_pos);
#ifdef debug
                std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" selects target "<<_which_target<<std::endl;
#endif
                return true;
            }
        }
        else
        {
            for(unsigned int i=0;i<all_tasks_.size();i++)
                if(all_tasks_[i].allocation_task_info.istarget==true&&all_tasks_[i].allocation_task_info.iscomplete==false
                   &&my_robot_.allocation_robot_info.robot_power>=all_tasks_[i].allocation_task_info.known_power
                   &&my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos)<all_tasks_[i].allocation_task_info.current_distance-3*LOCATION_ERROR)
                {
                    //cout<<all_tasks_[i].allocation_task_info.task_ID<<" "<<all_tasks_[i].allocation_task_info.current_distance<<endl;
                    distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos);
                    distance_vec.push_back(distance);
                    lab_vec.push_back(i);
                }
            //choose the target base on the probability
            if(distance_vec.size()!=0)
                for(unsigned int i=0;i<distance_vec.size();i++)
                {
                    if(distance_vec[i]!=0)
                        sum_possible=sum_possible+1000/distance_vec[i];
                    else
                    {
                        my_robot_.allocation_robot_info.which_target=all_tasks_[lab_vec[i]].allocation_task_info.task_ID;
                        my_robot_.allocation_robot_info.robot_mode=PLAN;
                        return true;
                    }
                    possible_vec.push_back(sum_possible);
                }
#ifdef debug
            else
                std::cout<<"There is not applicable target for Robot"<<my_robot_.allocation_robot_info.robot_ID<<std::endl;
#endif
            if(possible_vec.size()>0)
            {
                srand(clock());
                int tmp=rand()%(sum_possible);
                for(unsigned int i=0;i<possible_vec.size();i++)
                    if(tmp<possible_vec[i])
                    {
                        my_robot_.allocation_robot_info.which_target=all_tasks_[lab_vec[i]].allocation_task_info.task_ID;
                        my_robot_.allocation_robot_info.robot_mode=PLAN;
                        _which_target=my_robot_.allocation_robot_info.which_target;
                        all_tasks_[_which_target].allocation_task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[_which_target].gazebo_task_info.task_pos);
#ifdef debug
                        std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" selects target "<<_which_target<<std::endl;
#endif
                        return true;
                    }
            }
        }
    }

    //if do not find the target, reset the reriable for task selecting
    distance_vec.clear();
    possible_vec.clear();
    power_vec.clear();
    lab_vec.clear();
    distance=0;
    sum_possible=0;
    //there is no available target, but there are tasks uncomplete
    if(num_task_valid_>0)
    {
        if(!terminal_info_.greedorprobability)
        {
            float less_distance2=1000;
            //choose the nearest region for exploration
            for(unsigned int i=0;i<all_tasks_.size();i++)
                if(all_tasks_[i].allocation_task_info.istarget==false&&all_tasks_[i].allocation_task_info.isexplored==false
                   &&my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos)<all_tasks_[i].allocation_task_info.current_distance)
                {
                    distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos);
                    if(distance<less_distance2)
                    {
                        less_distance2=distance;
                        my_robot_.allocation_robot_info.which_task=all_tasks_[i].allocation_task_info.task_ID;
                    }
                }
            if(my_robot_.allocation_robot_info.which_task!=-1)
            {
                my_robot_.allocation_robot_info.robot_mode=PLAN;
                _which_task=my_robot_.allocation_robot_info.which_task;
                all_tasks_[_which_task].allocation_task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[_which_task].gazebo_task_info.task_pos);
#ifdef debug
                std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" selects task "<<_which_task<<std::endl;
#endif
                return true;
            }
        }
        else
        {
            for(unsigned int i=0;i<all_tasks_.size();i++)
                if(all_tasks_[i].allocation_task_info.istarget==false&&all_tasks_[i].allocation_task_info.isexplored==false
                   &&my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos)<all_tasks_[i].allocation_task_info.current_distance-3*LOCATION_ERROR)
                {
                    distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos);
                    distance_vec.push_back(distance);
                    lab_vec.push_back(i);
                }
            //choose the task base on the probability
            if(distance_vec.size()!=0)
                for(unsigned int i=0;i<distance_vec.size();i++)
                {
                    if(distance_vec[i]!=0)
                        sum_possible=sum_possible+1000/distance_vec[i];
                    else
                    {
                        my_robot_.allocation_robot_info.which_task=all_tasks_[lab_vec[i]].allocation_task_info.task_ID;
                        my_robot_.allocation_robot_info.robot_mode=PLAN;
                        return true;
                    }
                    possible_vec.push_back(sum_possible);
                }
#ifdef debug
            else
                std::cout<<"There is not applicable task for Robot"<<my_robot_.allocation_robot_info.robot_ID<<std::endl;
#endif
            if(possible_vec.size()>0)
            {
                srand(clock());
                int tmp=rand()%(sum_possible);
                for(unsigned int i=0;i<possible_vec.size();i++)
                    if(tmp<possible_vec[i])
                    {
//                        std::cout<<lab_vec[i]<<": "<<all_tasks_[lab_vec[i]].allocation_task_info.task_ID<<std::endl;
                        my_robot_.allocation_robot_info.which_task=all_tasks_[lab_vec[i]].allocation_task_info.task_ID;
                        my_robot_.allocation_robot_info.robot_mode=PLAN;
                        _which_task=my_robot_.allocation_robot_info.which_task;
                        all_tasks_[_which_task].allocation_task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[_which_task].gazebo_task_info.task_pos);
#ifdef debug
                        std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" selects task "<<_which_task<<std::endl;
#endif
                        return true;
                    }
            }
        }
    }
    return true;
}

/// \brief choose one robot to execute for avalid targets
bool Task_Allocation::which2hit_()
{
    if(!num_target_unallocated_)
        return false;

    float less_distance,distance;
    //choose the nearest robot for every unallocated target
    for(unsigned int i=0;i<all_tasks_.size();i++)
        if(all_tasks_[i].allocation_task_info.istarget==true&&all_tasks_[i].allocation_task_info.iscomplete==false&&
           all_tasks_[i].allocation_task_info.isallocated==false&&all_tasks_[i].allocation_task_info.task_power<my_robot_.allocation_robot_info.robot_power)
        {
            less_distance=my_robot_.allocation_robot_info.expect_pos.distance(all_tasks_[i].gazebo_task_info.task_pos);
            for(unsigned int j=0;j<all_robots_.size();j++)
            {
                if(all_robots_[j].allocation_robot_info.isvalid && all_robots_[j].allocation_robot_info.robot_ID!=my_robot_.allocation_robot_info.robot_ID&&
                   all_tasks_[i].allocation_task_info.task_power<all_robots_[j].allocation_robot_info.robot_power)
                {
                    distance=all_robots_[j].allocation_robot_info.expect_pos.distance(all_tasks_[i].gazebo_task_info.task_pos);
                    //if there is some robot near than me, this target will not allocated to me
                    if(distance<less_distance||(distance==less_distance&&my_robot_.allocation_robot_info.robot_ID>all_robots_[j].allocation_robot_info.robot_ID))
                        return false;
                }
                //i am the nearest robot and win the auction
                if(j==all_robots_.size()-1)
                {
                    my_robot_.allocation_robot_info.target_list.push_back(all_tasks_[i].allocation_task_info.task_ID);
                    my_robot_.allocation_robot_info.expect_pos=all_tasks_[i].gazebo_task_info.task_pos;
                    all_tasks_[i].allocation_task_info.isallocated=true;
                    return true;
                }
            }
        }
    //no target has been added to the list
    return false;
}

/// \brief choose one robot to execute for avalid tasks
bool Task_Allocation::which2explore_()
{
    if(!num_task_unallocated_)
        return false;

    float less_distance,distance;
    vector<int> task_list;
    for(unsigned int i=0;i<all_tasks_.size();i++)
        task_list.push_back(i);
    //reorder the valid task
    for(unsigned int i=0;i<all_tasks_.size()-1;i++)
    {
        for(unsigned int j=0;j<all_tasks_.size()-(i+1);j++)
        {
            double tmp_dis1=my_robot_.allocation_robot_info.expect_pos.distance(all_tasks_[task_list[j]].gazebo_task_info.task_pos);
            double tmp_dis2=my_robot_.allocation_robot_info.expect_pos.distance(all_tasks_[task_list[j+1]].gazebo_task_info.task_pos);
            if(tmp_dis1>tmp_dis2)
            {
                int tmp_list=task_list[j];
                task_list[j]=task_list[j+1];
                task_list[j+1]=tmp_list;
            }
        }
    }
    //choose the nearest robot for every unallocated task
    for(unsigned int i=0;i<all_tasks_.size();i++)
        if(all_tasks_[task_list[i]].allocation_task_info.istarget==false&&all_tasks_[task_list[i]].allocation_task_info.isexplored==false
           &&all_tasks_[task_list[i]].allocation_task_info.isallocated==false)
        {
            less_distance=my_robot_.allocation_robot_info.expect_pos.distance(all_tasks_[task_list[i]].gazebo_task_info.task_pos);
            for(unsigned int j=0;j<all_robots_.size();j++)
            {
                if(all_robots_[j].allocation_robot_info.isvalid && all_robots_[j].allocation_robot_info.robot_ID!=my_robot_.allocation_robot_info.robot_ID)
                {
                    distance=all_robots_[j].allocation_robot_info.expect_pos.distance(all_tasks_[task_list[i]].gazebo_task_info.task_pos);
                    //if there is some robot near than me, this target will not allocated to me
                    if(distance<less_distance||(distance==less_distance&&my_robot_.allocation_robot_info.robot_ID>all_robots_[j].allocation_robot_info.robot_ID))
                        return false;
                }
                //i am the nearest robot and win the auction
                if(j==all_robots_.size()-1&&all_robots_.size()==1)
                {
                    std::vector<int>::iterator it;
                    it = my_robot_.allocation_robot_info.task_list.begin();
                    float add_distance;
                    float min_add_distance=1000;
                    int insert_label=my_robot_.allocation_robot_info.task_list.size();
                    for(unsigned int p=1;p<my_robot_.allocation_robot_info.task_list.size()+1;p++)
                    {
                        if(p==my_robot_.allocation_robot_info.task_list.size())
                            add_distance=all_tasks_[my_robot_.allocation_robot_info.task_list[p-1]].gazebo_task_info.task_pos.distance(all_tasks_[task_list[i]].gazebo_task_info.task_pos);
                        else
                            add_distance=all_tasks_[my_robot_.allocation_robot_info.task_list[p-1]].gazebo_task_info.task_pos.distance(all_tasks_[task_list[i]].gazebo_task_info.task_pos)
                                    +all_tasks_[task_list[i]].gazebo_task_info.task_pos.distance(all_tasks_[my_robot_.allocation_robot_info.task_list[p]].gazebo_task_info.task_pos)
                                    -all_tasks_[my_robot_.allocation_robot_info.task_list[p-1]].gazebo_task_info.task_pos.distance(all_tasks_[my_robot_.allocation_robot_info.task_list[p]].gazebo_task_info.task_pos);
                        if(add_distance<min_add_distance)
                        {
                            min_add_distance=add_distance;
                            insert_label=p;
                        }
                    }
                    if(insert_label==my_robot_.allocation_robot_info.task_list.size())
                    {
                        my_robot_.allocation_robot_info.task_list.push_back(all_tasks_[task_list[i]].allocation_task_info.task_ID);
                        my_robot_.allocation_robot_info.expect_pos=all_tasks_[task_list[i]].gazebo_task_info.task_pos;
                    }
                    else
                        my_robot_.allocation_robot_info.task_list.insert(it+insert_label,all_tasks_[task_list[i]].allocation_task_info.task_ID);

                    all_tasks_[task_list[i]].allocation_task_info.isallocated=true;
                    return true;
                }
                else if(j==all_robots_.size()-1)
                {
                    my_robot_.allocation_robot_info.task_list.push_back(all_tasks_[task_list[i]].allocation_task_info.task_ID);
                    my_robot_.allocation_robot_info.expect_pos=all_tasks_[task_list[i]].gazebo_task_info.task_pos;
                    all_tasks_[task_list[i]].allocation_task_info.isallocated=true;
                    return true;
                }
            }
        }
    //no task has been added to the list
    return false;
}

/// \brief choose the next task using DQN
bool Task_Allocation::choose_task_()
{
    //initialization the variable
    int _which_target=-1;
    int _which_task=-1;

    //prepare the observation info for the DQN
    allocation_common::GetAction srv;
    srv.request.observation.Agent_ID=my_robot_.gazebo_robot_info.robot_ID;
    srv.request.observation.robot_pos.x=my_robot_.gazebo_robot_info.robot_pos.x_;
    srv.request.observation.robot_pos.y=my_robot_.gazebo_robot_info.robot_pos.y_;

    allocation_common::Teammateinfo teammateinfo;
    for(unsigned int i; i<all_robots_.size(); i++)
        if(all_robots_[i].allocation_robot_info.robot_ID!=my_robot_.allocation_robot_info.robot_ID)
        {
            Gazebo_robot_info tmp_gazebo=all_robots_[i].gazebo_robot_info;
            Allocation_robot_info tmp_allocation=all_robots_[i].allocation_robot_info;
            if(all_robots_[i].allocation_robot_info.isvalid)
            {
                teammateinfo.robot_pos.x=tmp_gazebo.robot_pos.x_;
                teammateinfo.robot_pos.y=tmp_gazebo.robot_pos.y_;
                teammateinfo.which_task=tmp_allocation.which_target!=-1? tmp_allocation.which_target:
                                                                         tmp_allocation.which_task;

//                teammateinfo.which_task=tmp_allocation.which_target!=-1? tmp_allocation.which_target:
//                                                                         tmp_allocation.which_task;
//                if(teammateinfo.which_task==-1)
//                {
//                    teammateinfo.robot_pos.x=tmp_gazebo.robot_pos.x_;
//                    teammateinfo.robot_pos.y=tmp_gazebo.robot_pos.y_;
//                }
//                else
//                {
//                    teammateinfo.robot_pos.x=all_tasks_[teammateinfo.which_task].gazebo_task_info.task_pos.x_;
//                    teammateinfo.robot_pos.y=all_tasks_[teammateinfo.which_task].gazebo_task_info.task_pos.y_;
//                }
            }
            else
            {
                teammateinfo.robot_pos.x=-1000;
                teammateinfo.robot_pos.y=-1000;
                teammateinfo.which_task=-1;
            }
            srv.request.observation.teammatesinfo.push_back(teammateinfo);
        }

    allocation_common::Taskinfo taskinfo;
    for(unsigned int i; i<all_tasks_.size();i++)
    {
        Gazebo_task_info tmp_gazebo=all_tasks_[i].gazebo_task_info;
        Allocation_task_info tmp_allocation=all_tasks_[i].allocation_task_info;

        taskinfo.task_ID=tmp_gazebo.task_ID;
        taskinfo.is_target=tmp_allocation.istarget==true? 1:0;
        if(tmp_allocation.iscomplete)
            taskinfo.task_status=0;
        else if(tmp_allocation.isexplored)
            taskinfo.task_status=1;
        else if(tmp_allocation.isallocated)
            taskinfo.task_status=2;
        else
            taskinfo.task_status=3;

//        if(taskinfo.task_status==3)
//        {
//            taskinfo.task_pos.x=0;
//            taskinfo.task_pos.y=0;
//        }
//        else
//        {
//            taskinfo.task_pos.x=tmp_gazebo.task_pos.x_;
//            taskinfo.task_pos.y=tmp_gazebo.task_pos.y_;
//        }
        taskinfo.task_pos.x=tmp_gazebo.task_pos.x_;
        taskinfo.task_pos.y=tmp_gazebo.task_pos.y_;
        srv.request.observation.tasksinfo.push_back(taskinfo);
    }
    //input the observation into the DQN and return the action
    if(get_action_client_.call(srv))
    {
        if(srv.response.action==-1)
        {
            ROS_ERROR("Failed to allocate task");
            return false;
        }
        else if(srv.response.action==0)
        {
#ifdef debug
            std::cout<<"don't allocate any task"<<std::endl;
#endif
            return true;
        }
        srv.response.action-=1;
//        ROS_INFO("action: %d", (int)srv.response.action);
        start_point_=my_robot_.gazebo_robot_info.robot_pos;
        Allocation_task_info tmp=all_tasks_[srv.response.action].allocation_task_info;
        if(tmp.istarget)
        {
            //the target has been completed
            if(tmp.iscomplete)
            {
                //return_rewrad_(Invalid_task);
                return false;
            }
            else
            {
                my_robot_.allocation_robot_info.which_target=srv.response.action;
                my_robot_.allocation_robot_info.robot_mode=PLAN;
                _which_target=my_robot_.allocation_robot_info.which_target;
                all_tasks_[_which_target].allocation_task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[_which_target].gazebo_task_info.task_pos);
                all_tasks_[_which_target].allocation_task_info.isallocated=true;
                //return_rewrad_(Valid_task, all_tasks_[_which_target].gazebo_task_info.task_pos);
#ifdef debug
                std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" selects target "<<_which_target<<std::endl;
#endif
            }
        }
        else
        {
            if(tmp.isexplored)
            {
                //return_rewrad_(Invalid_task);
                return false;
            }
            else
            {
                my_robot_.allocation_robot_info.which_task=srv.response.action;
                my_robot_.allocation_robot_info.robot_mode=PLAN;
                _which_task=my_robot_.allocation_robot_info.which_task;
                all_tasks_[_which_task].allocation_task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[_which_task].gazebo_task_info.task_pos);
                all_tasks_[_which_task].allocation_task_info.isallocated=true;
                //return_rewrad_(Valid_task, all_tasks_[_which_task].gazebo_task_info.task_pos);
#ifdef debug
                std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" selects task "<<_which_task<<std::endl;
#endif
            }
        }
    }
    else
    {
        ROS_ERROR("Failed to call service");
        return false;
    }

    return true;
}

/// \brief return the reward and the observation_ to the DQN
bool Task_Allocation::return_rewrad_(char causes, DPoint task_pos)
{
    //prepare the observation_ info for the DQN
    allocation_common::ReturnReward srv;
    srv.request.observation_.Agent_ID=my_robot_.gazebo_robot_info.robot_ID;
    srv.request.observation_.robot_pos.x=my_robot_.gazebo_robot_info.robot_pos.x_;
    srv.request.observation_.robot_pos.y=my_robot_.gazebo_robot_info.robot_pos.y_;

    allocation_common::Teammateinfo teammateinfo;
    for(unsigned int i; i<all_robots_.size(); i++)
        if(all_robots_[i].allocation_robot_info.robot_ID!=my_robot_.allocation_robot_info.robot_ID)
        {
            Gazebo_robot_info tmp_gazebo=all_robots_[i].gazebo_robot_info;
            Allocation_robot_info tmp_allocation=all_robots_[i].allocation_robot_info;
            if(all_robots_[i].allocation_robot_info.isvalid)
            {
                teammateinfo.robot_pos.x=tmp_gazebo.robot_pos.x_;
                teammateinfo.robot_pos.y=tmp_gazebo.robot_pos.y_;
                teammateinfo.which_task=tmp_allocation.which_target!=-1? tmp_allocation.which_target:
                                                                         tmp_allocation.which_task;

//                teammateinfo.which_task=tmp_allocation.which_target!=-1? tmp_allocation.which_target:
//                                                                         tmp_allocation.which_task;
//                if(teammateinfo.which_task==-1)
//                {
//                    teammateinfo.robot_pos.x=tmp_gazebo.robot_pos.x_;
//                    teammateinfo.robot_pos.y=tmp_gazebo.robot_pos.y_;
//                }
//                else
//                {
//                    teammateinfo.robot_pos.x=all_tasks_[teammateinfo.which_task].gazebo_task_info.task_pos.x_;
//                    teammateinfo.robot_pos.y=all_tasks_[teammateinfo.which_task].gazebo_task_info.task_pos.y_;
//                }
            }
            else
            {
                teammateinfo.robot_pos.x=-1000;
                teammateinfo.robot_pos.y=-1000;
                teammateinfo.which_task=-1;
            }
            srv.request.observation_.teammatesinfo.push_back(teammateinfo);
        }

    allocation_common::Taskinfo taskinfo;
    int _complete_tasks=0;
    int _explore_tasks=0;
    int _allocate_tasks=0;
    for(unsigned int i; i<all_tasks_.size();i++)
    {
        Gazebo_task_info tmp_gazebo=all_tasks_[i].gazebo_task_info;
        Allocation_task_info tmp_allocation=all_tasks_[i].allocation_task_info;

        taskinfo.task_ID=tmp_gazebo.task_ID;
        taskinfo.is_target=tmp_allocation.istarget==true? 1:0;
        if(tmp_allocation.iscomplete)
        {
            _complete_tasks++;
            taskinfo.task_status=0;
        }
        else if(tmp_allocation.isexplored)
        {
            _explore_tasks++;
            taskinfo.task_status=1;
        }
        else if(tmp_allocation.isallocated)
        {
            _allocate_tasks++;
            taskinfo.task_status=2;
        }
        else
            taskinfo.task_status=3;

//        if(taskinfo.task_status==3)
//        {
//            taskinfo.task_pos.x=0;
//            taskinfo.task_pos.y=0;
//        }
//        else
//        {
//            taskinfo.task_pos.x=tmp_gazebo.task_pos.x_;
//            taskinfo.task_pos.y=tmp_gazebo.task_pos.y_;
//        }
        taskinfo.task_pos.x=tmp_gazebo.task_pos.x_;
        taskinfo.task_pos.y=tmp_gazebo.task_pos.y_;
        srv.request.observation_.tasksinfo.push_back(taskinfo);
    }
    //return the reward to the DQN
    float _tmp_reward=0;
    float _max_distance=6*1.414;
    static float _invalid_tasks=0;
    static float _total_reward=0;
    switch (causes)
    {
    case Invalid_task:
        //_invalid_tasks+=1;
        _tmp_reward= -0.5
                     -(all_tasks_.size()-_allocate_tasks)/all_tasks_.size();
//        std::cout<<"Invalid_task: "<<_tmp_reward<<std::endl;
        break;
    case Valid_task:
        _invalid_tasks=0;
        _tmp_reward= (_max_distance-my_robot_.gazebo_robot_info.robot_pos.distance(task_pos))/_max_distance;
                     //+_allocate_tasks/all_tasks_.size();
//        std::cout<<"Valid_task: "<<_tmp_reward<<std::endl;
        break;
    case Drop_task:
        _invalid_tasks+=1;
        _tmp_reward= -my_robot_.gazebo_robot_info.robot_pos.distance(start_point_)/_max_distance;
                     //-(all_tasks_.size()-_allocate_tasks)/all_tasks_.size();
//        std::cout<<"Drop_task: "<<_tmp_reward<<std::endl;
        break;
    case Complete_target:
        _invalid_tasks=0;
        _tmp_reward= (_max_distance-my_robot_.gazebo_robot_info.robot_pos.distance(start_point_))/_max_distance;
                     //+_complete_tasks/all_tasks_.size();
//        std::cout<<"Complete_target: "<<_tmp_reward<<std::endl;
        break;
    case Explore_task:
        _invalid_tasks=0;
        _tmp_reward= (_max_distance-my_robot_.gazebo_robot_info.robot_pos.distance(start_point_))/_max_distance;
                     //+_explore_tasks/all_tasks_.size();
//        std::cout<<"Explore_task: "<<_tmp_reward<<std::endl;
        break;
    case Robot_damage:
        _invalid_tasks=0;
        _tmp_reward= -1;
        break;
    case All_complete:
//        std::cout<<"total_reward: "<<_total_reward<<std::endl;
        _total_reward=0;
        _invalid_tasks=0;
        _tmp_reward=0;
        srv.request.is_done=is_all_completed;
    default:
        break;
    }
    srv.request.reward=_tmp_reward;
    _total_reward+=_tmp_reward;
    if (return_reward_client_.call(srv))
    {
        if (!srv.response.is_train)
        {
            ROS_ERROR("The space of the observation is unmatched");
            return false;
        }
#ifdef debug
//        ROS_INFO("Run a train");
#endif
    }
    else
    {
        ROS_ERROR("Failed to call service");
        return false;
    }
}

/// \brief control cycle
void Task_Allocation::loopControl(const ros::TimerEvent &event)
{
//    //static int count=0;
//    if(my_robot_.allocation_robot_info.robot_ID==1)//&&count<10000)
//    {
//        terminal_info_.allocation_method=Prediction;
//        count++;
//        if(count==10000)
//            std::cout<<"agent "<<my_robot_.allocation_robot_info.robot_ID<<" begin DQN"<<std::endl;
//    }
//    else
//        terminal_info_.allocation_method=DQN;

    //reset some flag
    bid_new_task_=false;
    bid_new_target_=false;
    is_target_completed=false;
    is_task_explored=false;

    if(terminal_info_.allocation_mode==ALLOCATION_STOP)
        stopAllocation();
    else if(terminal_info_.allocation_mode==ALLOCATION_PAUSE)
        pauseAllocation();

    else if(is_all_completed)
        return;

    else if(!my_robot_.allocation_robot_info.isvalid)
    {
        //when the robot has been destroyed, the taskes in the task-list and target-list will be released (market-base method)
        if(terminal_info_.allocation_method==Market)
        {
            if(my_robot_.allocation_robot_info.target_list.size())
            {
                int _which_target=my_robot_.allocation_robot_info.target_list.back();
                all_tasks_[_which_target].allocation_task_info.isallocated=false;
                bid_new_target_=true;
                pubAllocation_info();
                my_robot_.allocation_robot_info.target_list.pop_back();
            }
            else if(my_robot_.allocation_robot_info.task_list.size())
            {
                int _which_task=my_robot_.allocation_robot_info.task_list.back();
                all_tasks_[_which_task].allocation_task_info.isallocated=false;
                bid_new_task_=true;
                pubAllocation_info();
                my_robot_.allocation_robot_info.task_list.pop_back();
            }
        }
        return;
    }

    //using prediction method to complete the allocation
    else if(terminal_info_.allocation_mode==ALLOCATION_START&&terminal_info_.allocation_method==Prediction)
    {
        //robot has complete the all task which allocated to it
        if(my_robot_.allocation_robot_info.which_target==-1&&my_robot_.allocation_robot_info.which_task==-1)
        {
            if(!choose2hitOrexplore_())
            {
                //all tasks have been completed
#ifdef debug
                std::cout<<"All tasks have been completed!"<<std::endl;
#endif
                is_all_completed=true;
                return;
                //allocation_timer_.stop();
            }
        }
        //the allocated target is not completed
        else if(my_robot_.allocation_robot_info.which_target!=-1)
        {
            is_target_completed=try2hit_();
#ifdef debug
            if(is_target_completed)
                std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" destroy the target "<<my_robot_.allocation_robot_info.which_target<<std::endl;
#endif
        }
        //the allocated task is not explored
        else if(my_robot_.allocation_robot_info.which_task!=-1)
        {
            is_task_explored=try2explore_();
#ifdef debug
            if(is_task_explored)
                std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" explore the task "<<my_robot_.allocation_robot_info.which_task<<std::endl;
#endif
        }
        pubAllocation_info();

        //if the task or target is done or dropped, clear the task or target
        if((my_robot_.allocation_robot_info.robot_mode==EXPLORE&&is_task_explored)||my_robot_.allocation_robot_info.robot_mode==IDLE)
        {
            if(my_robot_.allocation_robot_info.robot_mode==EXPLORE&&is_task_explored)
                my_robot_.allocation_robot_info.robot_mode=IDLE;
            my_robot_.allocation_robot_info.which_task=-1;
        }
        if((my_robot_.allocation_robot_info.robot_mode==HIT&&is_target_completed)||my_robot_.allocation_robot_info.robot_mode==DAMAGE||my_robot_.allocation_robot_info.robot_mode==IDLE)
        {
            if(my_robot_.allocation_robot_info.robot_mode==HIT&&is_target_completed)
                my_robot_.allocation_robot_info.robot_mode=IDLE;
            my_robot_.allocation_robot_info.which_target=-1;
        }
        setVelCommond();
        pubDrawing_info();
    }
    //using market-base method to complete the allocation
    else if(terminal_info_.allocation_mode==ALLOCATION_START&&terminal_info_.allocation_method==Market)
    {
        //there are residual task/target that unallocated
        if(num_target_unallocated_!=0)
        {
            my_robot_.allocation_robot_info.robot_mode=PLAN;
            bid_new_target_=which2hit_();
            if(bid_new_target_)
            {
                pubAllocation_info();
#ifdef debug
                std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" bid a new target "<<my_robot_.allocation_robot_info.target_list.back()<<std::endl;
#endif
            }
        }
        else if(num_task_unallocated_!=0)
        {
            my_robot_.allocation_robot_info.robot_mode=PLAN;
            bid_new_task_=which2explore_();
            if(bid_new_task_)
            {
                pubAllocation_info();
#ifdef debug
                std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" bid a new task "<<my_robot_.allocation_robot_info.task_list.back()<<std::endl;
#endif
            }
        }
        //the allocated target is not complete
        else if(my_robot_.allocation_robot_info.target_list.size()!=0)
        {
            is_target_completed=try2hit_();
            pubAllocation_info();
            if(is_target_completed)
            {
                //the target has been completed, delete it from the target_list
#ifdef debug
                std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" destroy the target "<<my_robot_.allocation_robot_info.target_list.front()<<std::endl;
#endif
                my_robot_.allocation_robot_info.target_list.erase(my_robot_.allocation_robot_info.target_list.begin());
            }
        }
        else if(my_robot_.allocation_robot_info.task_list.size()!=0)
        {
            my_robot_.allocation_robot_info.expect_pos=my_robot_.gazebo_robot_info.robot_pos;
            is_task_explored=try2explore_();
            pubAllocation_info();
            if(is_task_explored)
            {
                //the task has been explored, delete it from the task_list
#ifdef debug
                std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" explore the task "<<my_robot_.allocation_robot_info.task_list.front()<<std::endl;
#endif
                my_robot_.allocation_robot_info.task_list.erase(my_robot_.allocation_robot_info.task_list.begin());
            }
        }
        else if(!num_target_valid_&&!num_task_valid_)
        {
#ifdef debug
            std::cout<<"All tasks have been completed!"<<std::endl;
#endif
            is_all_completed=true;
            return;
        }
        setVelCommond();
        pubDrawing_info();
    }
    //using DQN method to complete the allocation
    else if(terminal_info_.allocation_mode==ALLOCATION_START&&terminal_info_.allocation_method==DQN)
    {
        //robot has complete the all task which allocated to it
        if(my_robot_.allocation_robot_info.which_target==-1&&my_robot_.allocation_robot_info.which_task==-1)
        {
            if(!num_target_valid_&&!num_task_valid_)
            {
                //all tasks have been completed
#ifdef debug
                std::cout<<"All tasks have been completed!"<<std::endl;
#endif
                is_all_completed=true;
                //return_rewrad_(All_complete);
                return;
            }
            else if(!choose_task_())
#ifdef debug
                std::cout<<"get an invalid task!"<<std::endl;
#else
                ;
#endif
        }
        //the allocated target is not completed
        else if(my_robot_.allocation_robot_info.which_target!=-1)
        {
            is_target_completed=try2hit_();
#ifdef debug
            if(is_target_completed)
                std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" destroy the target "<<my_robot_.allocation_robot_info.which_target<<std::endl;
#endif
        }
        //the allocated task is not explored
        else if(my_robot_.allocation_robot_info.which_task!=-1)
        {
            is_task_explored=try2explore_();
#ifdef debug
            if(is_task_explored)
                std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" explore the task "<<my_robot_.allocation_robot_info.which_task<<std::endl;
#endif
        }
        pubAllocation_info();

        //if the task or target is done or dropped, clear the task or target
        if((my_robot_.allocation_robot_info.robot_mode==EXPLORE&&is_task_explored)||my_robot_.allocation_robot_info.robot_mode==IDLE)
        {
            if(my_robot_.allocation_robot_info.robot_mode==EXPLORE&&is_task_explored)
                my_robot_.allocation_robot_info.robot_mode=IDLE;
            my_robot_.allocation_robot_info.which_task=-1;
        }
        if((my_robot_.allocation_robot_info.robot_mode==HIT&&is_target_completed)||my_robot_.allocation_robot_info.robot_mode==DAMAGE||my_robot_.allocation_robot_info.robot_mode==IDLE)
        {
            if(my_robot_.allocation_robot_info.robot_mode==HIT&&is_target_completed)
                my_robot_.allocation_robot_info.robot_mode=IDLE;
            my_robot_.allocation_robot_info.which_target=-1;
        }
        setVelCommond();
        pubDrawing_info();
    }
}

/// \brief pub the robot velocity, control the model in the gazebo
void Task_Allocation::setVelCommond()
{
    allocation_common::robot2gazebo_info _robot2gazebo_info;

    _robot2gazebo_info.robot_twist.linear.x=my_behaviour_->app_vx_;
    _robot2gazebo_info.robot_twist.linear.y=my_behaviour_->app_vy_;
    _robot2gazebo_info.robot_twist.angular=my_behaviour_->app_w_;
    _robot2gazebo_info.current_mode=my_robot_.allocation_robot_info.robot_mode;

    //clear velocity
    my_behaviour_->app_vx_=0;
    my_behaviour_->app_vy_=0;
    my_behaviour_->app_w_=0;

    robot2gazebo_pub_.publish(_robot2gazebo_info);
}

/// \brief pub the allocation_info include the robot_info and the task_info
void Task_Allocation::pubAllocation_info()
{
    allocation_common::allocation2terminal_info _allocation_info;
    int _which_target=-1;
    int _which_task=-1;

    _allocation_info.robot_info.robot_ID=my_robot_.allocation_robot_info.robot_ID;
    _allocation_info.robot_info.robot_mode=my_robot_.allocation_robot_info.robot_mode;
    _allocation_info.robot_info.isvalid=my_robot_.allocation_robot_info.isvalid;
    _allocation_info.robot_info.move_distance=my_robot_.allocation_robot_info.move_distance;
    if(terminal_info_.allocation_method==Prediction||terminal_info_.allocation_method==DQN)
    {
        _allocation_info.robot_info.which_task=my_robot_.allocation_robot_info.which_task;
        _allocation_info.robot_info.which_target=my_robot_.allocation_robot_info.which_target;
        _which_target=my_robot_.allocation_robot_info.which_target;
        _which_task=my_robot_.allocation_robot_info.which_task;
    }
    else
    {
        _allocation_info.robot_info.expect_pos.position.x=my_robot_.allocation_robot_info.expect_pos.x_;
        _allocation_info.robot_info.expect_pos.position.y=my_robot_.allocation_robot_info.expect_pos.y_;
        if(bid_new_target_)
            _which_target=my_robot_.allocation_robot_info.target_list.back();
        else if(is_target_completed)
            _which_target=my_robot_.allocation_robot_info.target_list.front();
        else if(bid_new_task_)
            _which_task=my_robot_.allocation_robot_info.task_list.back();
        else if(is_task_explored)
            _which_task=my_robot_.allocation_robot_info.task_list.front();
    }

    if(_which_target!=-1)
    {
        Allocation_task_info _target_info=all_tasks_[_which_target].allocation_task_info;

        _allocation_info.task_info.task_ID=_target_info.task_ID;
        _allocation_info.task_info.current_distance=_target_info.current_distance;
        _allocation_info.task_info.isallocated=_target_info.isallocated;
        if(my_robot_.allocation_robot_info.robot_mode==HIT||my_robot_.allocation_robot_info.robot_mode==DAMAGE)
        {
            _allocation_info.task_info.known_power=_target_info.known_power;
            _allocation_info.task_info.iscomplete=_target_info.iscomplete;
        }
    }
    else if(_which_task!=-1)
    {
        Allocation_task_info _task_info=all_tasks_[_which_task].allocation_task_info;

        _allocation_info.task_info.task_ID=_task_info.task_ID;
        _allocation_info.task_info.current_distance=_task_info.current_distance;
        _allocation_info.task_info.isallocated=_task_info.isallocated;
        if(my_robot_.allocation_robot_info.robot_mode==EXPLORE)
        {
            _allocation_info.task_info.known_power=_task_info.known_power;
            _allocation_info.task_info.istarget=_task_info.istarget;
            _allocation_info.task_info.iscomplete=_task_info.iscomplete;
            _allocation_info.task_info.isexplored=_task_info.isexplored;
        }
    }
    else
        _allocation_info.task_info.task_ID=-1;

    allocation2terminal_pub_.publish(_allocation_info);
}

/// \brief pub the info for drawing the robots' path
void Task_Allocation::pubDrawing_info()
{
    geometry_msgs::Point _drawing_info;

    _drawing_info.z=my_robot_.allocation_robot_info.robot_mode;
    _drawing_info.x=my_robot_.gazebo_robot_info.robot_pos.x_;
    _drawing_info.y=my_robot_.gazebo_robot_info.robot_pos.y_;

    drawing_pub_.publish(_drawing_info);
}

/// \brief when the controlterminal click "PAUSE", clear the robot velocity
void Task_Allocation::pauseAllocation()
{
    //clear velocity
    my_behaviour_->app_vx_=0;
    my_behaviour_->app_vy_=0;
    my_behaviour_->app_w_=0;
    setVelCommond();
}

/// \brief when the controlterminal click "STOP", reset all robots and tasks
void Task_Allocation::stopAllocation()
{
    //if these allocation info have reset yet
    if(all_robots_.size()==0)
        return;
    //clear velocity
    my_behaviour_->app_vx_=0;
    my_behaviour_->app_vy_=0;
    my_behaviour_->app_w_=0;

    //reset
    num_task_valid_=1;
    num_target_valid_=0;
    num_task_unallocated_=1;
    num_target_unallocated_=0;
    is_world_update_=false;
    bid_new_task_=false;
    bid_new_target_=false;
    is_target_completed=false;
    is_task_explored=false;
    is_all_completed=false;
    all_tasks_.clear();
    all_robots_.clear();

    my_robot_.allocation_robot_info.robot_reset();
    setVelCommond();
}

/// \brief read the parameters from the dynamic_reconfigure
void Task_Allocation::ParamChanged(dqn_ros::reward_cfgConfig &config, uint32_t level)
{
    Reward_I = config.Reward_I;
    Reward_D = config.Reward_D;
    Reward_C = config.Reward_C;
    Reward_E = config.Reward_E;
    Reward_R = config.Reward_R;
}
