#ifndef SUBTARGETS_H
#define SUBTARGETS_H

#include "Common.hpp"

class Subtargets
{
public:
        Subtargets();
        int
        Min_num(int n,double *q);
        double
        Min(int n,double *q);
        int
        Max_num(int n,double *q);
        double
        Max(int n,double *q);
        void
        subtarget(DPoint target, DPoint robot_pos_);
    
public:
        std::vector<DPoint> *Obstacles_;
        DPoint subtargets_pos_;
        DPoint robot_pos_;
        DPoint ball_pos_;
};
#endif //SUBTARGETS_H	 

