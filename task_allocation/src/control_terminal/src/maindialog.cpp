#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(Terminal2Gazebo_info &terminal2gazebo_info, Terminal2Robots_info &terminal2robots_info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    //the pointer in the maindialog point to the value which define in the topic_info
    terminal2gazebo_info_=& terminal2gazebo_info;
    terminal2robots_info_=& terminal2robots_info;

    //init ui
    ui->setupUi(this);

    //put the same kind itmes in the qlist
    agent_power_<<ui->power_1<<ui->power_2<<ui->power_3<<ui->power_4<<ui->power_5
                <<ui->power_6<<ui->power_7<<ui->power_8<<ui->power_9<<ui->power_10;
    agent_vaild_<<ui->agent_1<<ui->agent_2<<ui->agent_3<<ui->agent_4<<ui->agent_5
                <<ui->agent_6<<ui->agent_7<<ui->agent_8<<ui->agent_9<<ui->agent_10;

    timer_=new QTimer(this);
    connect(timer_,SIGNAL(timeout()),this,SLOT(timerUpdate()));

    num_targets_=0;
    num_agents_=0;

    for(int i=0;i<MAXNUM_AGENT;i++)
        agent_vaild_[i]->setCheckable(true);
    this->resize(370,690);

    isfirst_in_=true;
    current_steps_=0;
    current_time_=0;
    terminal2gazebo_info_->ismap_recreate_=false;

    ui->steps_show->setText("0");
    ui->time_show->setText("0");
    ui->target_show->setText("0");
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::update_info()
{

}

//accorrding to the number of agents load robots' processes
bool MainDialog::load_robotsprcess()
{
    num_agents_=0;
    for(int i=0;i<MAXNUM_AGENT;i++)
        if(agent_vaild_[i]->isChecked())
            num_agents_++;
    std::string str_num_agents="="+std::to_string(num_agents_)+" ";
    if(num_agents_==10)
        str_num_agents="="+std::to_string(num_agents_);               //the 10 has 2 number
    const char *char_num_agents=str_num_agents.c_str();

    char linebuffer[512] = {0};          //put the one line of the file in the line buffer
    char buffer1[512] = {0};             //put the first part of the line in the buffer1
    char buffer2[512] = {0};             //put the second part of the line in the buffer2
    
    int line_length=0;
    int length=0;
    int res;

    //open file "dynamic_allocation.sh"
    FILE *fp=fopen("dynamic_allocation.sh","r+");
    if(fp==NULL)
    {
        perror("open error");
        return false;
    }
    while(fgets(linebuffer,512,fp))
    {
        line_length=strlen(linebuffer);
        length+=line_length;
        sscanf(linebuffer,"%[^=]",buffer1);
        if(!strcmp("agent_num",buffer1))            //if buffer1="agent_num=",buffer2 is the number
        {
            length-=strlen(linebuffer);             //find the head of the line
            res=fseek(fp,length,SEEK_SET);          //find where we want to write
            if(res<0)
            {
                perror("fseek error");
                return false;
            }
            strcpy(buffer2,char_num_agents);
            strcat(buffer1,buffer2);
            fprintf(fp,"%s",buffer1);
            fclose(fp);
            return true;
        }
    }
    return false;
}

void MainDialog::timerUpdate()
{
    //start is clicked
    if(ui->start_pause->text()==QString("PAUSE"))
    {
//        if(ui->prediction->isChecked())
//            process_prediction_();
//        else if(ui->market_base->isChecked())
//            process_marketbase_();

        current_time_++;
        ui->steps_show->setText(QString::number(current_steps_));
        ui->time_show->setText(QString::number(current_time_));
    }
}

//recreate a map with specified size
void MainDialog::on_init_map_clicked()
{
    terminal2gazebo_info_->map_height_=ui->height_in->value();
    terminal2gazebo_info_->map_width_=ui->width_in->value();
    terminal2gazebo_info_->map_room_=ui->room_in->value();
    terminal2gazebo_info_->ismap_recreate_=true;

    if(terminal2gazebo_info_->map_room_>terminal2gazebo_info_->map_height_*terminal2gazebo_info_->map_width_)
    {
        notice_->information(this,"Warning","The number of rooms is too large",QMessageBox::Ok);
        return;
    }
}

void MainDialog::on_start_pause_clicked()
{
    if(ui->start_pause->text()==QString("START"))
    {
        //first click the START
        if(isfirst_in_)
        {
            if(load_robotsprcess())
                if(!system("./dynamic_allocation.sh"))
                    perror("start process failed");

//            my_taskallocation_->mutativeorconstant_=ui->constant_start->isChecked();
//            my_taskallocation_->init_agents_();
//            if(my_taskallocation_->my_agent_.size()==0)
//                return;
//            my_taskallocation_->init_task_=my_taskallocation_->my_task_;
            isfirst_in_=false;
//            my_taskallocation_->greedorprobability_=ui->probability->isChecked();
//            my_taskallocation_->recordornot_=ui->record->isChecked();
//            my_taskallocation_->powerordistance_=ui->distance->isChecked();

//            for(int i=0;i<MAXNUM_AGENT;i++)
//                if(agent_vaild_[i]->isChecked())
//                    item_agent_.push_back(map_->addPixmap(pix_agent_[i]));
//            for(int i=0;i<item_agent_.size();i++)
//            {
//                int init_pos_x=my_taskallocation_->my_agent_[i].init_posX_;
//                int init_pos_y=my_taskallocation_->my_agent_[i].init_posY_;
//                item_agent_[i]->setPos(init_pos_y*ui->map_scene->height()/ui->height_in->value()+bias_,
//                                       init_pos_x*ui->map_scene->width()/ui->width_in->value()+bias_);
//            }
//            timer_->start();
        }
        ui->start_pause->setText("PAUSE");
    }
    else
        ui->start_pause->setText("START");
}

void MainDialog::on_stop_clicked()
{
    current_steps_=0;
    current_time_=0;
    ui->steps_show->setText(QString::number(current_steps_));
    ui->time_show->setText(QString::number(current_time_));

    //复位Agent按键
    QString agent_str[MAXNUM_AGENT]={"1","2","3","4","5","6","7","8","9","X"};
    for(int i=0;i<MAXNUM_AGENT;i++)
    {
        agent_vaild_[i]->setText("Agent"+agent_str[i]);
        agent_vaild_[i]->setChecked(false);
    }
    ui->start_pause->setText("START");
    isfirst_in_=true;
}

void MainDialog::on_step_clicked()
{
//    //单步运行
//    if(ui->prediction->isChecked())
//        process_prediction_();
//    else if(ui->market_base->isChecked())
//        process_marketbase_();

    current_time_++;
    ui->steps_show->setText(QString::number(current_steps_));
    ui->time_show->setText(QString::number(current_time_));
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
