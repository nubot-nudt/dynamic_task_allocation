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
#include <QVector>
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
    void update_info();
    bool init_robots();

public:
    /**ui items**/
    Ui::MainDialog *ui;

    QList<QSpinBox*> agent_power_;
    QList<QPushButton*> agent_vaild_;
    QMessageBox *notice_;
    QTimer *timer_;

    QVector<QVector<bool>>  init_tasks_;
    QVector<QVector<int>>   init_targets_;
    QVector<QVector<bool>>  lab_tasks_;
    QVector<QVector<int>>   lab_targets_;

    Terminal2Gazebo_info* terminal2gazebo_info_;
    Terminal2Robots_info* terminal2robots_info_;

    ros::NodeHandle nh_;
    int  num_robots_;
    int  num_tasks_;

    QTime   current_time_;
    double  duration_time_;                         //record the duration time
    double  tmp_time_;

private slots:
    void timerUpdate();
    bool on_init_map_clicked();
    void on_start_pause_clicked();
    void on_stop_clicked();
    void on_power_clicked();
    void on_distance_clicked();
};

#endif // MAINDIALOG_H
