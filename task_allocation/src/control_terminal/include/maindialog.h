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
#include <iostream>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(Terminal2Gazebo_info &terminal2gazebo_info, Terminal2Robots_info &terminal2robots_info, QWidget *parent = 0);
    ~MainDialog();
    void update_info();
    bool load_robotsprcess();

public:
    /**ui items**/
    Ui::MainDialog *ui;

    QList<QSpinBox*> agent_power_;
    QList<QPushButton*> agent_vaild_;
    QMessageBox *notice_;
    QTimer *timer_;

    QVector<QVector<bool>>  init_room_;
    QVector<QVector<int>>   init_target_;
    QVector<QVector<bool>>  lab_room_;
    QVector<QVector<int>>   lab_target_;

    Terminal2Gazebo_info * terminal2gazebo_info_;
    Terminal2Robots_info * terminal2robots_info_;

    int  num_agents_;
    int  num_targets_;
    bool isfirst_in_;                                      //is first click start
    int  current_steps_;                                   //record the steps
    int  current_time_;                                    //record the time

private slots:
    void timerUpdate();
    void on_init_map_clicked();
    void on_start_pause_clicked();
    void on_stop_clicked();
    void on_step_clicked();
    void on_power_clicked();
    void on_distance_clicked();
};

#endif // MAINDIALOG_H
