#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QtCore>
#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <QSpinBox>
#include <QDebug>
#include <topic_info.h>
#include <stdio.h>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(Terminal2Gazebo_info &terminal2gazebo_info, Terminal2Robots_info &terminal2robots_info, QWidget *parent = 0);
    ~MainDialog();
    bool init_robots();
    void restart_game(int count);
public:
    /**ui items**/
    Ui::MainDialog *ui;

    QList<QSpinBox*> agent_power_;
    QList<QPushButton*> agent_vaild_;
    QList<QLineEdit*> agent_distance_;
    QMessageBox *notice_;
    QTimer *timer_;

    QVector<QVector<int>>  lab_tasks_;
    QVector<QString>  task_info_show_;

    Terminal2Gazebo_info* terminal2gazebo_info_;
    Terminal2Robots_info* terminal2robots_info_;

    ros::NodeHandle nh_;
    int  num_robots_;
    int  num_tasks_;

    QTime   current_time_;
    QString current_mode_;
    double  duration_time_;                          //record the duration time
    double  tmp_time_;
    bool    is_robot_exsit_;                         //is robot exsit in the gazebo

private slots:
    void timerUpdate();
    bool on_init_map_clicked();
    void on_start_pause_clicked();
    void on_stop_clicked();
    void on_show_more_clicked();
};

#endif // MAINDIALOG_H
