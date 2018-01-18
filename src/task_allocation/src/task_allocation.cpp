#include "task_allocation.h"

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
    gazebo2world_sub_  =nh_->subscribe("/allocation_gazebo/gazebo2world_info",10,&Task_Allocation::update_gazebo_world,this);
    terminal2robot_sub_=nh_->subscribe("/control_terminal/terminal2robot_info",10,&Task_Allocation::update_terminal_info,this);
    allocation_timer_  =nh_->createTimer(ros::Duration(0.03),&Task_Allocation::loopControl,this);
    my_behaviour_=new Behaviour(obstacles_);

    num_task_valid_=0;
    num_target_valid_=0;
    greedorprobability_=true;
    is_world_update_=false;
    all_tasks_.clear();
    all_robots_.clear();

    my_robot_.allocation_robot_info.isvalid=true;
}

Task_Allocation::~Task_Allocation()
{
    num_task_valid_=0;
    num_target_valid_=0;
    greedorprobability_=true;
    is_world_update_=false;
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

        //if the robot_ID is me
        if(_robot_info_tmp.robot_ID==my_robot_.gazebo_robot_info.robot_ID)
            my_robot_.gazebo_robot_info=_robot_info_tmp;

        //if the robot_ID is not me, it is a obstacle
        else
            obstacles_.push_back(DPoint(_robot_info_tmp.robot_pos.x_,_robot_info_tmp.robot_pos.y_));
    }

    //first callback, if all_tasks is a null vector, resize its size according to the _msg from gazebo
    if(all_tasks_.size()==0)
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

/// \brief update the terminal info to control the allocation process
void Task_Allocation::update_terminal_info(const allocation_common::terminal2robot_info::ConstPtr &_msg)
{
    //first callback, if all_robots is a null vector, wait the gazebo_msg to initilize the vector
    if(all_robots_.size()==0)
        return;

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
            if(_msg->all_allocation_task_info[j].task_ID!=my_robot_.allocation_robot_info.which_target&&
               _msg->all_allocation_task_info[j].task_ID!=my_robot_.allocation_robot_info.which_task)
            {
                _task_info_tmp.task_ID=_msg->all_allocation_task_info[j].task_ID;
                _task_info_tmp.current_distance=_msg->all_allocation_task_info[j].current_distance;
                _task_info_tmp.iscomplete=_msg->all_allocation_task_info[j].iscomplete;
                _task_info_tmp.isexplored=_msg->all_allocation_task_info[j].isexplored;
                _task_info_tmp.istarget=_msg->all_allocation_task_info[j].istarget;
                _task_info_tmp.known_power=_msg->all_allocation_task_info[j].known_power;
                _task_info_tmp.task_power=_msg->all_allocation_task_info[j].task_power;

                //            std::cout<<_task_info_tmp.isexplored<<std::endl;
                all_tasks_[_task_info_tmp.task_ID].allocation_task_info=_task_info_tmp;
            }
        }
    }
    //update the uncomplete task and target
    for(unsigned int i=0;i<all_tasks_.size();i++)
    {
        if(!all_tasks_[i].allocation_task_info.iscomplete&&all_tasks_[i].allocation_task_info.istarget)
            _num_target++;
        if(!all_tasks_[i].allocation_task_info.isexplored)
            _num_task++;
    }

    num_task_valid_=_num_task;
    num_target_valid_=_num_target;

    terminal_info_.allocation_mode=_msg->allocation_mode;
    terminal_info_.greedorprobability=_msg->greedorprobability;
    terminal_info_.powerordistance=_msg->powerordistance;
    terminal_info_.recordornot=_msg->recordornot;
}

/// \brief the process that robot to explore the task
bool Task_Allocation::try2explore_()
{
    static int _explore_time=0;
    Task_info _my_task;
    _my_task=all_tasks_[my_robot_.allocation_robot_info.which_task];

    for(unsigned int i=0;i<all_robots_.size();i++)
        //there is an other robot ready for this task except me
        if(all_robots_[i].allocation_robot_info.robot_ID!=my_robot_.allocation_robot_info.robot_ID
           &&all_robots_[i].allocation_robot_info.which_task==my_robot_.allocation_robot_info.which_task
           &&all_robots_[i].allocation_robot_info.isvalid)
        {
            int distance_1=my_robot_.gazebo_robot_info.robot_pos.distance(_my_task.gazebo_task_info.task_pos);
            int distance_2=all_robots_[i].gazebo_robot_info.robot_pos.distance(_my_task.gazebo_task_info.task_pos);
            //other robot's distance is littler
            if(distance_1>=distance_2)
            {
                //drop this task
                my_robot_.allocation_robot_info.robot_mode=IDLE;
                std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" drops task "<<my_robot_.allocation_robot_info.which_task<<" because of robot "<<i<<std::endl;
                return false;
            }
        }

    my_robot_.allocation_robot_info.robot_mode=EXECUTE;
    //there is no conflict, continue to carry out the task
    if(my_robot_.gazebo_robot_info.robot_pos.distance(_my_task.gazebo_task_info.task_pos)>LOCATION_ERROR)
    {
        float thetaofr2t = _my_task.gazebo_task_info.task_pos.angle(my_robot_.gazebo_robot_info.robot_pos).radian_;
        my_behaviour_->move2Positionwithobs(3,6,_my_task.gazebo_task_info.task_pos,4,my_robot_.gazebo_robot_info.robot_pos,my_robot_.gazebo_robot_info.robot_ori);
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
            all_tasks_[my_robot_.allocation_robot_info.which_task].allocation_task_info.isexplored=true;
            //this is a target
            if(_my_task.allocation_task_info.task_power>0)
            {
                all_tasks_[my_robot_.allocation_robot_info.which_task].allocation_task_info.known_power=1;
                all_tasks_[my_robot_.allocation_robot_info.which_task].allocation_task_info.istarget=true;
                all_tasks_[my_robot_.allocation_robot_info.which_task].allocation_task_info.current_distance=1000;
            }
            else
                all_tasks_[my_robot_.allocation_robot_info.which_task].allocation_task_info.iscomplete=true;

            return true;
        }
    }
}

/// \brief  the process that robot to hit the target
bool Task_Allocation::try2hit_()
{
    static int _hit_time=0;
    Task_info _my_target;
    _my_target=all_tasks_[my_robot_.allocation_robot_info.which_target];

    for(unsigned int i=0;i<all_robots_.size();i++)
        //there is an other robot ready for this target except me
        if(all_robots_[i].allocation_robot_info.robot_ID!=my_robot_.allocation_robot_info.robot_ID
           &&all_robots_[i].allocation_robot_info.which_target==my_robot_.allocation_robot_info.which_target
           &&all_robots_[i].allocation_robot_info.isvalid)
        {
            int distance_1=my_robot_.gazebo_robot_info.robot_pos.distance(_my_target.gazebo_task_info.task_pos);
            int distance_2=all_robots_[i].gazebo_robot_info.robot_pos.distance(_my_target.gazebo_task_info.task_pos);
            //other robot's distance is littler
            if(distance_1>=distance_2)
            {
                //drop this target
                my_robot_.allocation_robot_info.robot_mode=IDLE;
                std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" drops target "<<my_robot_.allocation_robot_info.which_target<<" because of robot "<<i<<std::endl;
                return false;
            }
        }

    my_robot_.allocation_robot_info.robot_mode=EXECUTE;
    //there is no conflict, continue to carry out this target
    if(my_robot_.gazebo_robot_info.robot_pos.distance(_my_target.gazebo_task_info.task_pos)>LOCATION_ERROR)
    {
        float thetaofr2t = _my_target.gazebo_task_info.task_pos.angle(my_robot_.gazebo_robot_info.robot_pos).radian_;
        my_behaviour_->move2Positionwithobs(3,6,_my_target.gazebo_task_info.task_pos,4,my_robot_.gazebo_robot_info.robot_pos,my_robot_.gazebo_robot_info.robot_ori);
//        my_behaviour_->rotate2AbsOrienation(2,5,thetaofr2t,5,my_robot_.gazebo_robot_info.robot_ori);
        return false;
    }
    //reach the target position
    else
    {
        //if the target power bigger than the robot power, the robot will be destroyed
        if(_my_target.allocation_task_info.task_power>my_robot_.allocation_robot_info.robot_power)
        {
            my_robot_.allocation_robot_info.robot_mode=DAMAGE;
            all_tasks_[my_robot_.allocation_robot_info.which_target].allocation_task_info.known_power=my_robot_.allocation_robot_info.robot_power+1;
            all_tasks_[my_robot_.allocation_robot_info.which_target].allocation_task_info.current_distance=1000;
            my_robot_.allocation_robot_info.isvalid=false;

            return false;
        }
        //if the target power less than the robot power, the target be destroyed
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
                all_tasks_[my_robot_.allocation_robot_info.which_target].allocation_task_info.iscomplete=true;
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
    double distance=0;
    int sum_possible=0;

    if(!num_target_valid_&&!num_task_valid_)
        return false;

    //there are targets which uncomplete
    if(num_target_valid_>0)
    {
        //make choice base on greed or probability
        if(!greedorprobability_)
        {
            int less_distance=1000;
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
                    distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[i].gazebo_task_info.task_pos);
                    distance_vec.push_back(distance);
                    lab_vec.push_back(i);
                }
            //choose the target base on the probability
            if(distance_vec.size()==0)
                std::cout<<"There is not applicable target for Robot"<<my_robot_.allocation_robot_info.robot_ID<<std::endl;
            else
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
            if(possible_vec.size()>0)
            {
                srand(clock());
                int tmp=rand()%(sum_possible);
                for(unsigned int i=0;i<possible_vec.size();i++)
                    if(tmp<possible_vec[i])
                    {
                        my_robot_.allocation_robot_info.which_target=all_tasks_[lab_vec[i]].allocation_task_info.task_ID;
                        my_robot_.allocation_robot_info.robot_mode=PLAN;
                        std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" selects target "<<my_robot_.allocation_robot_info.which_target<<std::endl;
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
        if(!greedorprobability_)
        {
            int less_distance2=1000;
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
            if(distance_vec.size()==0)
                std::cout<<"There is not applicable task for Robot"<<my_robot_.allocation_robot_info.robot_ID<<std::endl;
            else
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
                        std::cout<<"robot"<<my_robot_.allocation_robot_info.robot_ID<<" selects task "<<my_robot_.allocation_robot_info.which_task<<std::endl;
                        return true;
                    }
            }
        }
    }
    return true;
}

/// \brief control cycle
void Task_Allocation::loopControl(const ros::TimerEvent &event)
{
    bool _is_target_completed=false;
    bool _is_task_explored=false;

    if(terminal_info_.allocation_mode==ALLOCATION_STOP)
        stopAllocation();
    else if(terminal_info_.allocation_mode==ALLOCATION_PAUSE)
        pauseAllocation();
    else if(terminal_info_.allocation_mode==ALLOCATION_START)
    {
        if(!my_robot_.allocation_robot_info.isvalid)
        {
            //if this robot is inviald, stop the loopcontrol
            std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" is destroyed!"<<std::endl;
            allocation_timer_.stop();
            return;
        }
        else
        {
            //robot has complete the all task which allocated to it
            if(my_robot_.allocation_robot_info.which_target==-1&&my_robot_.allocation_robot_info.which_task==-1)
            {
                if(!choose2hitOrexplore_())
                {
                    //all tasks have been completed
                    std::cout<<"All tasks have been completed!"<<std::endl;
                    //allocation_timer_.stop();
                    //return;
                }
            }
            //the allocated target is not completed
            if(my_robot_.allocation_robot_info.which_target!=-1)
            {
                _is_target_completed=try2hit_();
                if(_is_target_completed)
                    std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" destroy the target "<<my_robot_.allocation_robot_info.which_target<<std::endl;
            }
            else if(my_robot_.allocation_robot_info.which_task!=-1)
            {
                _is_task_explored=try2explore_();
                if(_is_task_explored)
                    std::cout<<"Robot"<<my_robot_.allocation_robot_info.robot_ID<<" explore the task "<<my_robot_.allocation_robot_info.which_task<<std::endl;
            }
        }
        pubAllocation_info();

        //if the task or target is done or dropped, clear the task or target
        if((my_robot_.allocation_robot_info.robot_mode==EXPLORE&&_is_task_explored)||my_robot_.allocation_robot_info.robot_mode==IDLE)
        {
            //std::cout<<"1"<<std::endl;
            if(my_robot_.allocation_robot_info.robot_mode==EXPLORE&&_is_task_explored)
                my_robot_.allocation_robot_info.robot_mode=IDLE;
            my_robot_.allocation_robot_info.which_task=-1;
        }
        if((my_robot_.allocation_robot_info.robot_mode==HIT&&_is_target_completed)||my_robot_.allocation_robot_info.robot_mode==DAMAGE||my_robot_.allocation_robot_info.robot_mode==IDLE)
        {
            //std::cout<<"2"<<std::endl;
            if(my_robot_.allocation_robot_info.robot_mode==HIT&&_is_target_completed)
                my_robot_.allocation_robot_info.robot_mode=IDLE;
            my_robot_.allocation_robot_info.which_target=-1;
        }
    }
    setVelCommond();
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
    static allocation_common::allocation2terminal_info _allocation_info;

    _allocation_info.robot_info.robot_ID=my_robot_.allocation_robot_info.robot_ID;
    _allocation_info.robot_info.robot_mode=my_robot_.allocation_robot_info.robot_mode;
    _allocation_info.robot_info.which_task=my_robot_.allocation_robot_info.which_task;
    _allocation_info.robot_info.which_target=my_robot_.allocation_robot_info.which_target;
    _allocation_info.robot_info.isvalid=my_robot_.allocation_robot_info.isvalid;

    if(my_robot_.allocation_robot_info.which_target!=-1&&
       (my_robot_.allocation_robot_info.robot_mode==EXECUTE||my_robot_.allocation_robot_info.robot_mode==HIT||my_robot_.allocation_robot_info.robot_mode==DAMAGE))
    {
        Allocation_task_info _target_info=all_tasks_[my_robot_.allocation_robot_info.which_target].allocation_task_info;
        if(my_robot_.allocation_robot_info.robot_mode==EXECUTE)
        {
            _target_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[my_robot_.allocation_robot_info.which_target].gazebo_task_info.task_pos);
            _allocation_info.task_info.current_distance=_target_info.current_distance;
        }

        else
        {
            _allocation_info.task_info.task_ID=_target_info.task_ID;
            _allocation_info.task_info.known_power=_target_info.known_power;
            _allocation_info.task_info.current_distance=_target_info.current_distance;
            _allocation_info.task_info.istarget=_target_info.istarget;
            _allocation_info.task_info.iscomplete=_target_info.iscomplete;
            _allocation_info.task_info.isexplored=_target_info.isexplored;
        }
    }
    else if(my_robot_.allocation_robot_info.which_task!=-1&&
            (my_robot_.allocation_robot_info.robot_mode==EXECUTE||my_robot_.allocation_robot_info.robot_mode==EXPLORE))
    {
        Allocation_task_info _task_info=all_tasks_[my_robot_.allocation_robot_info.which_task].allocation_task_info;
        if(my_robot_.allocation_robot_info.robot_mode==EXECUTE)
        {
            _task_info.current_distance=my_robot_.gazebo_robot_info.robot_pos.distance(all_tasks_[my_robot_.allocation_robot_info.which_task].gazebo_task_info.task_pos);
            _allocation_info.task_info.current_distance=_task_info.current_distance;
        }

        else
        {
            _allocation_info.task_info.task_ID=_task_info.task_ID;
            _allocation_info.task_info.known_power=_task_info.known_power;
            _allocation_info.task_info.current_distance=_task_info.current_distance;
            _allocation_info.task_info.istarget=_task_info.istarget;
            _allocation_info.task_info.iscomplete=_task_info.iscomplete;
            _allocation_info.task_info.isexplored=_task_info.isexplored;
        }
    }
    else
        _allocation_info.task_info.task_ID=-1;

    allocation2terminal_pub_.publish(_allocation_info);
}

/// \brief when the controlterminal click "PAUSE", clear the robot velocity
void Task_Allocation::pauseAllocation()
{
    //clear velocity
    my_behaviour_->app_vx_=0;
    my_behaviour_->app_vy_=0;
    my_behaviour_->app_w_=0;
}

/// \brief when the controlterminal click "STOP", reset all robots and tasks
void Task_Allocation::stopAllocation()
{
    //clear velocity
    my_behaviour_->app_vx_=0;
    my_behaviour_->app_vy_=0;
    my_behaviour_->app_w_=0;

    //reset
    num_task_valid_=0;
    num_target_valid_=0;
    greedorprobability_=true;
    is_world_update_=false;
    all_tasks_.clear();
    all_robots_.clear();

    my_robot_.allocation_robot_info.robot_reset();
}
