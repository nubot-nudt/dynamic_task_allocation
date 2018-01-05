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

    timer_=new QTimer(this);
    timer_->start(100);
    connect(timer_,SIGNAL(timeout()),this,SLOT(timerUpdate()));

    num_tasks_=0;
    num_robots_=0;

    for(int i=0;i<MAXNUM_AGENT;i++)
        agent_vaild_[i]->setCheckable(true);
    this->setFixedSize(370,690);

    //time initialization
    duration_time_=0;
    tmp_time_=0;

    terminal2robots_info_->allocation_mode=ALLOCATION_STOP;

    terminal2gazebo_info_->isNew_allocation=false;
    terminal2gazebo_info_->robot_pos_x.clear();
    terminal2gazebo_info_->robot_pos_y.clear();
    terminal2gazebo_info_->task_pos_x.clear();
    terminal2gazebo_info_->task_pos_y.clear();

    init_tasks_=lab_tasks_=QVector<QVector<bool>> (ui->height_in->value(),QVector<bool>(ui->width_in->value()));
    init_targets_=lab_targets_=QVector<QVector<int>> (ui->height_in->value(),QVector<int>(ui->width_in->value()));

    ui->steps_show->setText("0");
    ui->time_show->setText("0");
    ui->target_show->setText("0");
    ui->tasks_show->setText("0");
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::update_info()
{

}

/// \brief initialize the number of agents and map_height, map_width, put them in the rosparam, and all node can use
bool MainDialog::init_robots()
{
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

void MainDialog::timerUpdate()
{
    //start is clicked
    if(terminal2robots_info_->allocation_mode==ALLOCATION_START)
    {
        duration_time_=(tmp_time_*1000+current_time_.elapsed())/1000;
        ui->time_show->setText(QString::number(duration_time_));
    }
}

/// \brief recreate a map with specified size
bool MainDialog::on_init_map_clicked()
{
    //num_tasks
    num_tasks_=ui->tasks_num_in->value();
    //num_robots
    num_robots_=0;
    for(int i=0;i<MAXNUM_AGENT;i++)
        if(agent_vaild_[i]->isChecked())
            num_robots_++;

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
    int num=0;
    int task_power=0;
    int x_num=ui->height_in->value();
    int y_num=ui->width_in->value();
    lab_tasks_=QVector <QVector<bool>> (x_num,QVector<bool>(y_num));
    lab_targets_=QVector <QVector<int>> (x_num,QVector<int>(y_num));

    for(int i=0;i<num_tasks_;i++)
    {
        while(lab_tasks_[num/y_num][num%y_num]==1)
            num=qrand()%(x_num*y_num);

        lab_tasks_[num/y_num][num%y_num]=1;
        terminal2gazebo_info_->task_pos_x.push_back(num/y_num-x_num/2);
        terminal2gazebo_info_->task_pos_y.push_back(num%y_num-y_num/2);

        //initialize the power of task randomly
        task_power=qrand()%(20)-9;
        if(task_power>0)
            terminal2robots_info_->all_allocation_task_info[i].task_power=task_power;
        else
            terminal2robots_info_->all_allocation_task_info[i].task_power=0;
    }
    ui->tasks_show->setText(QString::number(num_tasks_));

    //initialize the position of robot
    for(int i=0;i<num_robots_;i++)
    {
        //robots place the left of allocation map
        terminal2gazebo_info_->robot_pos_x.push_back(-x_num/2-1);
        terminal2gazebo_info_->robot_pos_y.push_back(-y_num/2+i);

        //initialize the power of robot according to the button
        terminal2robots_info_->all_allocation_robot_info[i].robot_power=agent_power_[i]->value();
    }
    terminal2gazebo_info_->isNew_allocation=true;

    return true;
}

void MainDialog::on_start_pause_clicked()
{
    if(terminal2robots_info_->allocation_mode==ALLOCATION_STOP)
    {
        //first click the START
        if(!init_robots())
            perror("spawn robots failed");

        ui->start_pause->setText("PAUSE");
        terminal2robots_info_->allocation_mode=ALLOCATION_START;
        terminal2robots_info_->greedorprobability=ui->probability->isChecked();

        current_time_.start();
        tmp_time_=duration_time_;
    }
    else if(terminal2robots_info_->allocation_mode==ALLOCATION_START)
    {
        ui->start_pause->setText("START");
        terminal2robots_info_->allocation_mode=ALLOCATION_PAUSE;
    }
    else if(terminal2robots_info_->allocation_mode==ALLOCATION_PAUSE)
    {
        ui->start_pause->setText("PAUSE");
        terminal2robots_info_->allocation_mode=ALLOCATION_START;
        current_time_.start();
        tmp_time_=duration_time_;
    }
}

void MainDialog::on_stop_clicked()
{
    terminal2robots_info_->allocation_mode=ALLOCATION_STOP;
    ui->start_pause->setText("START");

    duration_time_=0;
    tmp_time_=0;
    ui->steps_show->setText("0");
    ui->time_show->setText("0");

    //reset the agent button
    QString agent_str[MAXNUM_AGENT]={"1","2","3","4","5","6","7","8","9","X"};
    for(int i=0;i<MAXNUM_AGENT;i++)
    {
        agent_vaild_[i]->setText("Agent"+agent_str[i]);
        agent_vaild_[i]->setChecked(false);
    }
}

void MainDialog::on_power_clicked()
{
    ui->greed->setChecked(false);
    ui->probability->setChecked(true);
    ui->greed->setDisabled(true);
}

void MainDialog::on_distance_clicked()
{
    ui->greed->setDisabled(false);
}
