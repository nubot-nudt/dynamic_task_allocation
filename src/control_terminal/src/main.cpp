#include "maindialog.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString myDir=QCoreApplication::applicationDirPath();
    QDir::setCurrent(myDir);                                                 //change the current Dir

    ros::init(argc,argv,"control_terminal_node");
    ROS_INFO("start control_terminal process");

    Topic_Info topic_info;
    MainDialog w(topic_info.terminal2gazebo_info,topic_info.terminal2robots_info);
    w.show();
    topic_info.start();
    return a.exec();
}
