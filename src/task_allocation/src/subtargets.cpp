#include "subtargets.h"

Subtargets::Subtargets()
{

}

int
Subtargets::Min_num(int n,double *q)              
{
    int min_out_num=0;
    for(int i=1;i<n;i++)
    {
        if(q[i]<q[min_out_num])
            min_out_num=i;
    }
    return min_out_num;
}

double
Subtargets::Min(int n,double *q)
{
    double min_out=q[0];
    for(int i=1;i<n;i++)
    {
        if(q[i]<min_out)
            min_out=q[i];
    }
    return min_out;
}

int
Subtargets::Max_num(int n,double *q)
{
    int max_out_num=0;
    for(int i=1;i<n;i++)
    {
        if(q[i]>q[max_out_num])
            max_out_num=i;
    }
    return max_out_num;
}

double
Subtargets::Max(int n,double *q)
{
    double max_out=q[0];
    for(int i=1;i<n;i++)
    {
        if(q[i]>max_out)
            max_out=q[i];
    }
    return max_out;
}

void
Subtargets::subtarget(DPoint target_pos_, DPoint robot_pos_)
{
    for(int c = Obstacles_->size();c<9;c++)
        Obstacles_->push_back(DPoint(10000,10000));

    double radius_robot=0.5,radius_Obs=0.5;
    double a[9],b[9];
    DPoint point_=target_pos_- robot_pos_;
    int i=0,j=0,k=0;
    int B[9]={0};
    int First_num=0;
    double minB=0;

    int G[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int G_num=0;
    int G_Obstacles_[9]={1,1,1,1,1,1,1,1,1};

    double b_positive[10]={0};
    double b_negative[10]={0};
    int left=0,right=0,sign_side=0,bp_num=0,bn_num=0;

    double atemp=0;
    double alpha[9]={0};
    double alpha_i=0;
    int    alpha_k=0;

    bool canpass=0;

    for(i=0;i<9;i++)
    {
        int temp=0;
        DPoint point1_= Obstacles_->at(i)- robot_pos_;
        if( point_.cross(point1_)==0 )
            temp=0;
        else if( point_.cross(point1_)>0 )
            temp=1;
        else
            temp=-1;

        a[i] = point_.ddot(point1_)/point_.norm();
        b[i] = temp*fabs(point_.cross(point1_))/point_.norm();
    }
    //obtain B that may hit
    for(i=0;i<9;i++)
    {
        if((a[i]>0)&&(a[i]<point_.norm())&&(fabs(b[i])<(radius_robot+radius_Obs)))
        {
            B[j]=i;
            j++;
        }
    }

    if(j!=0)
    {
        //determain first Obstacles_
        First_num=B[0];
        minB=a[B[0]];
        for(i=1;i<j;i++)
        {
            if(minB<a[B[i]])
                minB=minB;
            else
            {
                minB=a[B[i]];
                First_num=B[i];
            }
        }

        //Grouping--the Obstacles_ that must be avoided
        G[0]=First_num;
        G_num=0;
        G_Obstacles_[First_num]=0;

        for(i=0;i<9;i++)
        {
            if(G_Obstacles_[i]==1)
            {
                for(k=0;k<=G_num;k++)
                {
                    if(Obstacles_->at(i).distance(Obstacles_->at(G[k]))<(2*radius_robot+2*radius_Obs))
                    {
                        G_num++;
                        G[G_num]=i;
                        G_Obstacles_[i]=0;
                        i=-1;
                        break;
                    }
                }
            }
        }
        //Location of subtarget
        for(i=0;i<=G_num;i++)
        {
            if(b[G[i]]>0)
            {
                bp_num++;
                b_positive[bp_num]=b[G[i]];
            }
            else if(b[G[i]]<0)
            {
                bn_num++;
                b_negative[bn_num]=fabs(b[G[i]]);
            }
        }
        if(Max(10,b_positive)<=Max(10,b_negative))
        {
            left=1;
            sign_side=1;
        }
        else
        {
            right=1;
            sign_side=-1;
        }

        for(i=0;i<=G_num;i++)
        {
            atemp=Obstacles_->at(G[i]).distance(robot_pos_);
            if(atemp<(radius_robot+radius_Obs))
            {
                atemp=radius_robot+radius_Obs+0.0001;
                canpass=1;
            }
            alpha[i]=atan2(b[G[i]],a[G[i]])+sign_side*asin((radius_robot+radius_Obs)/atemp);
        }


        if(left==1)
        {
            alpha_i=Max(G_num+1,alpha);
            alpha_k=Max_num(G_num+1,alpha);
        }
        else
        {
            alpha_i=Min(G_num+1,alpha);
            alpha_k=Min_num(G_num+1,alpha);
        }
        subtargets_pos_.x_= robot_pos_.x_+(cos(alpha_i)*point_.x_-sin(alpha_i)*point_.y_)*Obstacles_->at(G[alpha_k]).distance(robot_pos_)/point_.norm();
        subtargets_pos_.y_= robot_pos_.y_+(sin(alpha_i)*point_.x_+cos(alpha_i)*point_.y_)*Obstacles_->at(G[alpha_k]).distance(robot_pos_)/point_.norm();
    }
    else
        subtargets_pos_=target_pos_;
}


