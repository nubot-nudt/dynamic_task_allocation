#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#include <subtargets.h>

class Behaviour
{

public:
    Behaviour(std::vector<DPoint> &obstacles);
    ~ Behaviour();

    float basicPDControl(float pgain,float dgain, float err,float err1, float maxval);
    void move2Position(float pval, float dval, DPoint target, float maxvel,
                       const DPoint  & _robot_pos,const Angle  & _robot_ori,bool avoid_obs, DPoint realtarvel=DPoint(0,0));
    void move2Positionwithobs(float pval, float dval, DPoint target, float maxvel,
                              const DPoint & _robot_pos, const Angle & _robot_ori);
    void rotate2AbsOrienation(float pval, float dval, float orientation,float maxw,const Angle & _robot_ori);
    void clearBehaviorState();
    void setAppvx(double vx);
    void setAppvy(double vy);
    void setAppw(double w);
    void accelerateLimit(const double &_acc_thresh = 25, const bool & use_convected_acc = true);
    void clear();
public:
    float app_vx_;
    float app_vy_;
    float app_w_;
    float last_app_vx_;
    float last_app_vy_;
    float last_app_w_;
    float last_speed;

    Subtargets m_subtargets_;
 };

#endif // _BEHAVIOUR_H
