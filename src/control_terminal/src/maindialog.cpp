#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(Terminal2Gazebo_info &terminal2gazebo_info, Terminal2Robots_info &terminal2robots_info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    //the pointer in the maindialog point to the value which define in the topic_info
    terminal2gazebo_info_= &terminal2gazebo_info;
    terminal2robots_info_= &terminal2robots_info;

    //init ui
    ui->setupUi(this);

    //put the same kind itmes in the qlist
    agent_power_<<ui->power_1<<ui->power_2<<ui->power_3<<ui->power_4<<ui->power_5
                <<ui->power_6<<ui->power_7<<ui->power_8<<ui->power_9<<ui->power_10;
    agent_vaild_<<ui->agent_1<<ui->agent_2<<ui->agent_3<<ui->agent_4<<ui->agent_5
                <<ui->agent_6<<ui->agent_7<<ui->agent_8<<ui->agent_9<<ui->agent_10;
    agent_distance_<<ui->dis_agent_1<<ui->dis_agent_2<<ui->dis_agent_3<<ui->dis_agent_4<<ui->dis_agent_5
                   <<ui->dis_agent_6<<ui->dis_agent_7<<ui->dis_agent_8<<ui->dis_agent_9<<ui->dis_agent_10;

    timer_=new QTimer(this);
    connect(timer_,SIGNAL(timeout()),this,SLOT(timerUpdate()));

    num_tasks_=0;
    num_robots_=0;

    for(int i=0;i<MAXNUM_AGENT;i++)
    {
        agent_vaild_[i]->setCheckable(true);
        agent_distance_[i]->setText("0");
    }

    this->setFixedSize(490,750);

    //time initialization
    duration_time_=0;
    tmp_time_=0;
    is_robot_exsit_=false;

    terminal2robots_info_->allocation_mode=ALLOCATION_STOP;
    terminal2robots_info_->greedorprobability=1;
    terminal2robots_info_->finish_train=false;
    terminal2robots_info_->finish_episode=false;
    //default use the prediction method
    terminal2robots_info_->allocation_method=Prediction;

    terminal2gazebo_info_->isNew_allocation=false;
    terminal2gazebo_info_->robot_pos_x.clear();
    terminal2gazebo_info_->robot_pos_y.clear();
    terminal2gazebo_info_->task_pos_x.clear();
    terminal2gazebo_info_->task_pos_y.clear();

    ui->time_show->setText("0");
    ui->target_show->setText("0");
    ui->tasks_show->setText("0");
}

MainDialog::~MainDialog()
{
    delete ui;
    if(is_robot_exsit_)
    {
        //get the task_allocation_node pid
        ROS_INFO("Delete the task_allocation_node");
        FILE *fp=NULL;
        char pid_line[64];
        fp=popen("pidof task_allocation_node","r");
        char *tmp=fgets(pid_line,64,fp);

        //kill the pids
        char pid_kill[128];
        strcpy(pid_kill, "kill ");
        strcat(pid_kill, pid_line);
        fp=popen(pid_kill,"r");
        pclose(fp);
    }
}

/// \brief initialize the number of agents and map_height, map_width, put them in the rosparam, and all node can use
bool MainDialog::init_robots()
{
    if(is_robot_exsit_)
        return true;
    else
    {
        is_robot_exsit_=true;
        //according to the UI input, change the param
        nh_.setParam("/control_terminal/robots_num", num_robots_);

        ROS_INFO("Spwan robots");
        FILE *fp = NULL;
        fp = popen("../../../src/allocation_common/spawn_robots.sh","w");
        if(fp == NULL)
            return false;
        pclose(fp);
        return true;
    }
}

/// \brief when the game is done, restart the game from begin point for DQN train
void MainDialog::restart_game(int count)
{
    //set the allocation_mode as STOP, then all of the parameters are initialized
    float total_distance=0;
    for(int i=0;i<MAXNUM_AGENT;i++)
        if(agent_vaild_[i]->isChecked())
        {
            total_distance += terminal2robots_info_->all_allocation_robot_info[i].move_distance;
            agent_vaild_[i]->setText("RESET");
            agent_distance_[i]->setText("0");
        }
    std::cout<<"duration_time: "<<duration_time_<<" , total_distance: "<<total_distance<<" , start the "<<count<<" episode!"<<std::endl;

    terminal2robots_info_->allocation_mode=ALLOCATION_STOP;
    duration_time_=tmp_time_=0;
    ui->time_show->setText("0");
    sleep(2);
    terminal2robots_info_->allocation_mode=ALLOCATION_START;
    current_time_.start();
}

void MainDialog::timerUpdate()
{
    //start is clicked
    if(terminal2robots_info_->allocation_mode==ALLOCATION_START)
    {
        duration_time_=(tmp_time_*1000+current_time_.elapsed())/1000;
        ui->time_show->setText(QString::number(duration_time_));
    }
    //show the mode of robot on the button
    int _total_distance=0;
    for(unsigned int i=0;i<MAXNUM_AGENT;i++)
        if(agent_vaild_[i]->isChecked())
        {
            switch(terminal2robots_info_->all_allocation_robot_info[i].robot_mode)
            {
            case 0: current_mode_="IDLE";break;
            case 1: current_mode_="PLAN";break;
            case 2: current_mode_="EXECUTE";break;
            case 3: current_mode_="EXPLORE";break;
            case 4: current_mode_="HIT";break;
            case 5: current_mode_="DAMAGE";break;
            case 6: current_mode_="RESET";break;
            default:break;
            }
            agent_vaild_[i]->setText(current_mode_);
            agent_distance_[i]->setText(QString::number(terminal2robots_info_->all_allocation_robot_info[i].move_distance));
            _total_distance += terminal2robots_info_->all_allocation_robot_info[i].move_distance;
        }
    //show task_information
    QString _allShow_combine;
    int _uncomplete_task=0;
    int _uncomplete_target=0;
    for(unsigned int i=0;i<num_tasks_;i++)
    {
        //update the uncomplete task and target
        if(!terminal2robots_info_->all_allocation_task_info[i].iscomplete&&terminal2robots_info_->all_allocation_task_info[i].istarget)
            _uncomplete_target++;
        if(!terminal2robots_info_->all_allocation_task_info[i].isexplored)
            _uncomplete_task++;

        Allocation_task_info _tmp_task_info=terminal2robots_info_->all_allocation_task_info[i];
        if(terminal2robots_info_->allocation_method==Prediction||terminal2robots_info_->allocation_method==DQN)
        {
            if(i<10)
                task_info_show_[i]=QString(" Task.%1  |          %2          |            %3           |       %4        |  (%5, %6)").arg(i).arg(_tmp_task_info.isexplored)
                        .arg(_tmp_task_info.iscomplete).arg(_tmp_task_info.istarget).arg(terminal2gazebo_info_->task_pos_x[i]).arg(terminal2gazebo_info_->task_pos_y[i]);
            else
                task_info_show_[i]=QString("Task.%1 |          %2          |            %3           |       %4        |  (%5, %6)").arg(i).arg(_tmp_task_info.isexplored)
                        .arg(_tmp_task_info.iscomplete).arg(_tmp_task_info.istarget).arg(terminal2gazebo_info_->task_pos_x[i]).arg(terminal2gazebo_info_->task_pos_y[i]);
        }
        else
        {
            if(i<10)
                task_info_show_[i]=QString(" Task.%1  |          %2          |            %3           |       %4        |  (%5, %6)").arg(i).arg(_tmp_task_info.isallocated)
                        .arg(_tmp_task_info.iscomplete).arg(_tmp_task_info.istarget).arg(terminal2gazebo_info_->task_pos_x[i]).arg(terminal2gazebo_info_->task_pos_y[i]);
            else
                task_info_show_[i]=QString("Task.%1 |          %2          |            %3           |       %4        |  (%5, %6)").arg(i).arg(_tmp_task_info.isallocated)
                        .arg(_tmp_task_info.iscomplete).arg(_tmp_task_info.istarget).arg(terminal2gazebo_info_->task_pos_x[i]).arg(terminal2gazebo_info_->task_pos_y[i]);
        }

        _allShow_combine=_allShow_combine+task_info_show_[i]+"\n";
    }
    ui->show_task_info->setText(_allShow_combine);
    ui->tasks_show->setText(QString::number(_uncomplete_task));
    ui->target_show->setText(QString::number(_uncomplete_target));
    //check whether the tasks are all completed
    bool _is_all_completed=true;
    static int count=1;
    for(unsigned int i=0;i<terminal2robots_info_->all_allocation_task_info.size();i++)
        if(!terminal2robots_info_->all_allocation_task_info[i].iscomplete)
        {
            _is_all_completed=false;
            break;
        }
    if(_is_all_completed)
    {
        if(terminal2robots_info_->allocation_method==DQN&&ui->train->isChecked()&&count<ui->episode_num_in->value())
        {
            count++;
            terminal2robots_info_->finish_episode=true;
            restart_game(count);
        }
        else if(terminal2robots_info_->allocation_method==DQN&&ui->train->isChecked())
        {
            count=1;
            terminal2robots_info_->finish_train=true;
            timer_->stop();
            notice_->information(this,"Notice","The train have been completed",QMessageBox::Ok);
        }
        else
        {
            timer_->stop();
            //terminal2robots_info_->allocation_mode=ALLOCATION_STOP;
            std::cout<<"duration_time: "<<duration_time_<<" , total_distance: "<<_total_distance<<std::endl;
            for(int i=0;i<terminal2robots_info_->all_allocation_robot_info.size();i++)
                std::cout<<terminal2robots_info_->all_allocation_robot_info[i].move_distance<<std::endl;
            notice_->information(this,"Notice","The all tasks have been completed",QMessageBox::Ok);
        }
    }
}

/// \brief recreate a map with specified size
bool MainDialog::on_init_map_clicked()
{
    if(is_robot_exsit_)
        return true;
    //num_tasks
    num_tasks_=ui->tasks_num_in->value();
    terminal2robots_info_->all_allocation_task_info.resize(num_tasks_);
    task_info_show_.resize(num_tasks_);
    //num_robots
    num_robots_=0;
    for(int i=0;i<MAXNUM_AGENT;i++)
        if(agent_vaild_[i]->isChecked())
            num_robots_++;
    terminal2robots_info_->all_allocation_robot_info.resize(num_robots_);

    if(ui->tasks_num_in->value() > ui->height_in->value()*ui->width_in->value())
    {
        notice_->information(this,"Warning","The number of tasks is too large",QMessageBox::Ok);
        return false;
    }
    else if(num_robots_==0)
    {
        notice_->information(this,"Warning","There is not any robot",QMessageBox::Ok);
        return false;
    }

    //initialize the position of task randomly
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int  num=0;
    int  task_power=0;
    int  x_num=ui->height_in->value();
    int  y_num=ui->width_in->value();
    lab_tasks_=QVector <QVector<int>> (x_num,QVector<int>(y_num,-1));

    for(int i=0;i<num_tasks_;i++)
    {
        while(lab_tasks_[num/y_num][num%y_num]>-1)
            num=qrand()%(x_num*y_num);

        terminal2gazebo_info_->task_pos_x.push_back(num/y_num-x_num/2);
        terminal2gazebo_info_->task_pos_y.push_back(num%y_num-y_num/2);

        //initialize the power of task randomly
        task_power=qrand()%(20)-9;
        if(task_power>0)
        {
            terminal2robots_info_->all_allocation_task_info[i].task_power=task_power;
            lab_tasks_[num/y_num][num%y_num]=task_power;
        }
        else
        {
            terminal2robots_info_->all_allocation_task_info[i].task_power=0;
            lab_tasks_[num/y_num][num%y_num]=0;
        }
    }
    ui->tasks_show->setText(QString::number(num_tasks_));

    int  _tmp;
    bool _tmp_pos[x_num][y_num]={0};
    //initialize the position of robot
    for(int i=0;i<num_robots_;i++)
    {
        //place the robots on left of allocation map
        if(!ui->random_pos->isChecked())
        {
            terminal2gazebo_info_->robot_pos_x.push_back(-x_num/2-1);
            terminal2gazebo_info_->robot_pos_y.push_back(-y_num/2+i);
        }
        //place the robots on the random position around the map
        else
        {
            _tmp=qrand()%(4);
            if(_tmp==0)
            {
                terminal2gazebo_info_->robot_pos_x.push_back(-x_num/2-1);
                while(_tmp_pos[0][_tmp])
                    _tmp=qrand()%(y_num);
                terminal2gazebo_info_->robot_pos_y.push_back(_tmp-y_num/2);
                _tmp_pos[0][_tmp]=true;
            }
            else if(_tmp==1)
            {
                terminal2gazebo_info_->robot_pos_x.push_back(x_num/2+1);
                while(_tmp_pos[x_num-1][_tmp])
                    _tmp=qrand()%(y_num);
                terminal2gazebo_info_->robot_pos_y.push_back(_tmp-y_num/2);
                _tmp_pos[x_num-1][_tmp]=true;
            }
            else if(_tmp==2)
            {
                terminal2gazebo_info_->robot_pos_y.push_back(-y_num/2-1);
                while(_tmp_pos[_tmp][0])
                    _tmp=qrand()%(x_num);
                terminal2gazebo_info_->robot_pos_x.push_back(_tmp-x_num/2);
                _tmp_pos[_tmp][0]=true;
            }
            else
            {
                terminal2gazebo_info_->robot_pos_y.push_back(y_num/2+1);
                while(_tmp_pos[_tmp][y_num-1])
                    _tmp=qrand()%(x_num);
                terminal2gazebo_info_->robot_pos_x.push_back(_tmp-x_num/2);
                _tmp_pos[_tmp][y_num-1]=true;
            }
        }

        //initialize the power of robot according to the button
        terminal2robots_info_->all_allocation_robot_info[i].robot_power=agent_power_[i]->value();
    }
    terminal2gazebo_info_->is_noise=ui->is_noise;
    terminal2gazebo_info_->isNew_allocation=true;

    return true;
}

void MainDialog::on_start_pause_clicked()
{
    if(terminal2robots_info_->allocation_mode==ALLOCATION_STOP)
    {
        if(num_tasks_==0&&num_robots_==0)
        {
            notice_->information(this,"Warning","Please init the map",QMessageBox::Ok);
            return;
        }
        //first click the START
        if(!init_robots())
            perror("spawn robots failed");

        ui->start_pause->setText("PAUSE");
        terminal2robots_info_->allocation_mode=ALLOCATION_START;
        terminal2robots_info_->greedorprobability=ui->probability->isChecked();
        if(ui->prediction->isChecked())
            terminal2robots_info_->allocation_method=Prediction;
        else if(ui->market_base->isChecked())
            terminal2robots_info_->allocation_method=Market;
        else
            terminal2robots_info_->allocation_method=DQN;

        current_time_.start();
        timer_->start(100);
        tmp_time_=duration_time_;
    }
    else if(terminal2robots_info_->allocation_mode==ALLOCATION_START)
    {
        ui->start_pause->setText("START");
        terminal2robots_info_->allocation_mode=ALLOCATION_PAUSE;
        timer_->stop();
    }
    else if(terminal2robots_info_->allocation_mode==ALLOCATION_PAUSE)
    {
        ui->start_pause->setText("PAUSE");
        terminal2robots_info_->allocation_mode=ALLOCATION_START;
        current_time_.start();
        timer_->start(100);
        tmp_time_=duration_time_;
    }
}

void MainDialog::on_stop_clicked()
{
    terminal2robots_info_->allocation_mode=ALLOCATION_STOP;
    ui->start_pause->setText("START");

    duration_time_=0;
    tmp_time_=0;
    ui->time_show->setText("0");

    for(int i=0;i<MAXNUM_AGENT;i++)
        if(agent_vaild_[i]->isChecked())
        {
            agent_vaild_[i]->setText("RESET");
            agent_distance_[i]->setText("0");
        }
}

void MainDialog::on_show_more_clicked()
{
    if(this->size().width()==990)
    {
        this->setFixedSize(490,750);
        ui->show_more->setText(">");
    }
    else
    {
        this->setFixedSize(990,750);
        ui->show_more->setText("<");
    }
}
