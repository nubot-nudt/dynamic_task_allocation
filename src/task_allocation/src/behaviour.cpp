#include "behaviour.h"

Behaviour::Behaviour(std::vector<DPoint> &obstacles)
{
    app_vx_ = 0;
    app_vy_ = 0;
    app_w_  = 0;
    last_app_vx_ = 0;
    last_app_vy_ = 0;
    last_app_w_ = 0;
    m_subtargets_.Obstacles_= &obstacles;
}

Behaviour::~Behaviour()
{
}

void Behaviour::clear()
{
    app_vx_ = 0;
    app_vy_ = 0;
    app_w_  = 0;
    last_app_vx_ = 0;
    last_app_vy_ = 0;
    last_app_w_ = 0;
}

float Behaviour::basicPDControl(float pgain,float dgain, float err,float err1, float maxval)
{
    float _e1 = err1;
    float kp =  pgain;
    float kd=  dgain;
    float _e=err;
    float retval = 0;
    retval  = kp *_e +kd*(_e -_e1) ;
    if(fabs(retval) > maxval)
    {
        if(retval>0) retval= maxval;
        else    retval=-maxval;
    }
    return retval;
}

/// \brief tranlation control move to the target point by using PD control
void Behaviour::move2Position(float pval, float dval, DPoint target, float maxvel,
                         const DPoint & _robot_pos, const Angle & _robot_ori, bool avoid_obs, DPoint realtarvel)
{
#if 1
    float _pos_e = _robot_pos.distance(target);
    DPoint relposoftarget =  target  - _robot_pos;
    float tar_theta = relposoftarget.angle().radian_;
    static float _pos_e1 = 0;
    float  speed = 0;
    speed = basicPDControl(pval,dval,_pos_e,_pos_e1,maxvel);
//    app_vx_ =  speed*cos(tar_theta - _robot_ori.radian_)+ realtarvel.x_;
//    app_vy_ =  speed*sin(tar_theta - _robot_ori.radian_)+ realtarvel.y_;
    //use vx,vy in world frame
    app_vx_ =  speed*cos(tar_theta)+ realtarvel.x_;
    app_vy_ =  speed*sin(tar_theta)+ realtarvel.y_;
    double v=sqrt(app_vx_*app_vx_+app_vy_*app_vy_);

    if(v>maxvel)
    {
        app_vx_=app_vx_*maxvel/v;
        app_vy_=app_vy_*maxvel/v;
    }
    _pos_e1  = _pos_e;
#else
    static float _pos_e1 = 0;
    static bool move_x=true;
    static bool move_y=true;
    float _pos_e=0;
    float  speed = 0;

    if(fabs(_robot_pos.x_-target.x_)>0.5)
        move_x=true;
    else if(fabs(_robot_pos.x_-target.x_)<0.1)
        move_x=false;

    if(fabs(_robot_pos.y_-target.y_)>0.5)
        move_y=true;
    else if(fabs(_robot_pos.y_-target.y_)<0.1)
        move_y=false;

    if(move_x&&!avoid_obs)
    {
        _pos_e = target.x_-_robot_pos.x_;
        speed = basicPDControl(pval,dval,_pos_e,_pos_e1,maxvel);
        app_vx_ = speed+realtarvel.x_;
        app_vy_ = 0;
    }
    else if(move_y&&!avoid_obs)
    {
        _pos_e = target.y_-_robot_pos.y_;
        speed = basicPDControl(pval,dval,_pos_e,_pos_e1,maxvel);
        app_vy_ = speed+realtarvel.y_;
        app_vx_ = 0;
    }
    else
    {
        _pos_e = _robot_pos.distance(target);
        DPoint relposoftarget =  target  - _robot_pos;
        float tar_theta = relposoftarget.angle().radian_;
        speed = basicPDControl(pval,dval,_pos_e,_pos_e1,maxvel);
        app_vx_ = speed*cos(tar_theta)+ realtarvel.x_;
        app_vy_ = speed*sin(tar_theta)+ realtarvel.y_;
    }
    _pos_e1  = _pos_e;
#endif
}

/// \brief move to the target point with avoiding obstacles
void Behaviour::move2Positionwithobs(float pval, float dval, DPoint target, float maxvel,
                                     const DPoint & _robot_pos, const Angle & _robot_ori)
{
    m_subtargets_.subtarget(target, _robot_pos);
    double theta;

    if(m_subtargets_.subtargets_pos_==target)
    {
        move2Position(pval,dval,target,maxvel,_robot_pos,_robot_ori,false);
        theta = thetaof2p(_robot_pos,target);
    }
    else
        move2Position(pval,dval,m_subtargets_.subtargets_pos_,maxvel,_robot_pos,_robot_ori,true);
}

/// \brief rotate to the target orientation by using PD control
void Behaviour::rotate2AbsOrienation(float pval, float dval, float orientation,float maxw,const Angle & _robot_ori)
{

    float theta_e = orientation -  _robot_ori.radian_;
    static float theta_e1 = 0;
    while(theta_e > SINGLEPI_CONSTANT) theta_e = theta_e-2*SINGLEPI_CONSTANT;
    while(theta_e <= -SINGLEPI_CONSTANT) theta_e = theta_e+2*SINGLEPI_CONSTANT;

    app_w_ = basicPDControl(pval,dval,theta_e,theta_e1,maxw);
    theta_e1 = theta_e ;

}

/// \brief the accelerate limit
void Behaviour::accelerateLimit(const double &_acc_thresh, const bool &use_convected_acc)
{
#define WHEELS 4
    const double WHEEL_DISTANCE=20.3;
    const double dcc_thresh = _acc_thresh*1.5;
    static float wheel_speed_old[WHEELS] = {0};
    float wheel_speed[WHEELS];
    float wheel_acc[WHEELS];
    float& Vx = app_vx_;
    float& Vy = app_vy_;
    float&  w = app_w_;

    if(WHEELS == 4)
    {
        wheel_speed[0]= ( 0.707*( Vx - Vy) - w*WHEEL_DISTANCE);
        wheel_speed[1]= ( 0.707*( Vx + Vy) - w*WHEEL_DISTANCE);
        wheel_speed[2]= ( 0.707*(-Vx + Vy) - w*WHEEL_DISTANCE);
        wheel_speed[3]= ( 0.707*(-Vx - Vy) - w*WHEEL_DISTANCE);
    }
    else
    {
        wheel_speed[0]= ( 0.866*Vx -  0.5*Vy - w*WHEEL_DISTANCE);
        wheel_speed[1]= (   0.0*Vx +      Vy - w*WHEEL_DISTANCE);
        wheel_speed[2]= ( -0.866*Vx - 0.5*Vy - w*WHEEL_DISTANCE);
    }
    float acc_thresh_ratio = 1;
    for(int i=0; i<WHEELS; i++)
    {
        wheel_acc[i] = wheel_speed[i]-wheel_speed_old[i];
        float acc_thresh_ratio_temp = 0;
        if( wheel_acc[i]*wheel_speed_old[i]>=0 )
            acc_thresh_ratio_temp = fabs(wheel_acc[i])/_acc_thresh;
        else
            acc_thresh_ratio_temp = fabs(wheel_acc[i])/dcc_thresh;
        if( acc_thresh_ratio_temp>acc_thresh_ratio )
            acc_thresh_ratio = acc_thresh_ratio_temp;
    }

    if( acc_thresh_ratio > 1 )
    {
        for(int i=0; i<WHEELS; i++)
        {
            wheel_acc[i] /= acc_thresh_ratio;
            wheel_speed[i] = wheel_speed_old[i] + wheel_acc[i];
        }
    }
    if(WHEELS==4)
    {
        w  = -(wheel_speed[0]+wheel_speed[1]+wheel_speed[2]+wheel_speed[3])/(4*WHEEL_DISTANCE);
        Vx =  (wheel_speed[0]+wheel_speed[1]-wheel_speed[2]-wheel_speed[3])/(2*1.414);
        Vy =  (wheel_speed[1]+wheel_speed[2]-wheel_speed[0]-wheel_speed[3])/(2*1.414);
    }
    else
    {
        Vx = ( 0.577*wheel_speed[0]  + 0 * wheel_speed[1] -  wheel_speed[2] * 0.577);
        Vy = (-0.333*wheel_speed[0]  + 0.667*wheel_speed[1] - wheel_speed[2]*0.333);
        w  = (-wheel_speed[0] - wheel_speed[1] - wheel_speed[2] )/(3*WHEEL_DISTANCE);
    }

    if(hypot(Vx,Vy)*fabs(w)*0.03>_acc_thresh)
    {
        float v_wheel=0;
        for(int i=0; i<WHEELS; i++)
        {
            if( fabs(wheel_speed[i])>v_wheel )
                v_wheel = fabs(wheel_speed[i]);
        }
        if(v_wheel<_acc_thresh) v_wheel = _acc_thresh;
        for(int i=0; i<WHEELS; i++)
        {
            wheel_speed[i] *= (1-_acc_thresh/v_wheel);
        }
        if(WHEELS==4)
        {
            w  = -(wheel_speed[0]+wheel_speed[1]+wheel_speed[2]+wheel_speed[3])/(4*WHEEL_DISTANCE);
            Vx =  (wheel_speed[0]+wheel_speed[1]-wheel_speed[2]-wheel_speed[3])/(2*1.414);
            Vy =  (wheel_speed[1]+wheel_speed[2]-wheel_speed[0]-wheel_speed[3])/(2*1.414);
        }
        else
        {
            Vx = ( 0.577*wheel_speed[0]  + 0 * wheel_speed[1] -  wheel_speed[2] * 0.577);
            Vy = (-0.333*wheel_speed[0]  + 0.667*wheel_speed[1] - wheel_speed[2]*0.333);
            w  = (-wheel_speed[0] - wheel_speed[1] - wheel_speed[2] )/(3*WHEEL_DISTANCE);
        }
    }
    if(use_convected_acc)
    {
        float temp = Vx;
        Vx -=-Vy*w*0.1;
        Vy -= temp*w*0.1;
    }
    for(int i=0; i<WHEELS; i++)
    {
        wheel_speed_old[i] = wheel_speed[i];
    }
}

void Behaviour::setAppvx(double vx){
    app_vx_ = vx;
}
void Behaviour::setAppvy(double vy){
    app_vy_ = vy;
}
void Behaviour::setAppw(double w){
    app_w_ = w;
}
