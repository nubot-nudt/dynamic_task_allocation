#ifndef COMMON_H
#define COMMON_H

#include <Core.hpp>

using namespace std;

inline float
angularnorm(float _x)
{
while (_x > SINGLEPI_CONSTANT)
    _x -= DOUBLEPI_CONSTANT;
while (_x < -SINGLEPI_CONSTANT)
    _x += DOUBLEPI_CONSTANT;
return _x;
}

inline DPoint
pglobal2rel(DPoint _gpos, float _ori, DPoint _tar_gpos)
{

  DPoint pos = _tar_gpos - _gpos;

  return DPoint(pos.x_*cos(_ori)+pos.y_*sin(_ori),
                  -pos.x_*sin(_ori)+pos.y_*cos(_ori));

}

inline DPoint
prel2global(DPoint _gpos, float _ori, DPoint _rel_pos)
{

    return  DPoint(_gpos.x_+_rel_pos.x_*cos(_ori)-_rel_pos.y_*sin(_ori),
                                        _gpos.y_+_rel_pos.x_*sin(_ori)+_rel_pos.y_*cos(_ori));

}

inline float
thetaof2p(DPoint begin, DPoint end)
{
   return  atan2(end.y_ - begin.y_, end.x_ - begin.x_);
}

inline float
thetaof2p2(DPoint begin, DPoint end)
{
    return atan2(end.x_ -  begin.x_, end.y_ - begin.y_);
}

inline float
thetaofpo(DPoint _pos)
{
   return atan2(_pos.y_,_pos.x_);
}


inline DPoint
vglobal2rel(DPoint _v, float _ori)
{

    return  DPoint(_v.x_*cos(_ori)+_v.y_*sin(_ori),
                                        -_v.x_*sin(_ori)+_v.y_*cos(_ori));

}


inline DPoint
vrel2global(DPoint _v, float _ori)
{
    return  DPoint(_v.x_*cos(_ori)-_v.y_*sin(_ori),
                                        _v.x_*sin(_ori)+_v.y_*cos(_ori));
}

inline float
sign(float _x)
{
    if(_x >= 0.00)
        return  1.0;
    else
        return -1.0;

}

inline DPoint
PointOfLine(DPoint P1, DPoint P2, double D)
{
    double theta = atan2(P2.y_-P1.y_,P2.x_-P1.x_);
    return DPoint(P1.x_+cos(theta)*D,P1.y_+sin(theta)*D);
}

inline DPoint
RotOfPoint(DPoint P1,DPoint P2,double Ang,bool Clockwise)//
{
    double theta = atan2(P1.y_-P2.y_,P1.x_-P2.x_);
    double dis= P1.distance(P2);
    if(Clockwise)
        theta=theta-Ang;
    else
        theta=theta+Ang;
    return DPoint(P2.x_+cos(theta)*dis,P2.y_+sin(theta)*dis);
}


inline double
Dis_2P(DPoint P1, DPoint P2)
{
    return sqrt((P1.x_-P2.x_)*(P1.x_-P2.x_)+(P1.y_-P2.y_)*(P1.y_-P2.y_));
}



inline DPoint
Vector_2P(DPoint P1,DPoint P2)
{
    return DPoint((P2.x_-P1.x_),(P2.y_-P1.y_));
}



inline double
Dis_P2Line(DPoint P1, DPoint P2, DPoint P)
{
    return ((P2.y_-P1.y_)*P.x_-(P2.x_-P1.x_)*P.y_+P2.x_*P1.y_-P1.x_*P2.y_)/Dis_2P(P1,P2);
}


inline double
Dis_P2Line(double A, double B, double C, DPoint P)
{
    return (A*P.x_+B*P.y_+C)/sqrt(A*A+B*B);
}


inline double
Dis_P2O(DPoint P)
{
    return sqrt(P.x_*P.x_+P.y_*P.y_);
}

inline DPoint
TangentPoint(DPoint Center, double radius, bool Left)
{
    double theta=atan2(Center.y_,Center.x_);
    double dis=sqrt(Center.x_*Center.x_+Center.y_*Center.y_);
    double theta_e;
    if(dis>radius)
    {
        theta_e=asin(radius/dis);
        dis=dis*cos(theta_e);
    }
    else
    {
        theta_e=SINGLEPI_CONSTANT/2;
        dis=50;
    }
    if(Left) theta=theta+theta_e;
    else     theta=theta-theta_e;
    return DPoint(dis*cos(theta),dis*sin(theta));
}


inline DPoint
TangentPoint(DPoint Point,DPoint Center, double radius, bool Left)
{

    double theta=atan2(Center.y_-Point.y_,Center.x_-Point.x_);
    double dis=Dis_2P(Center,Point);
    double theta_e;
    if(dis>radius)
    {
        theta_e=asin(radius/dis);
        dis=dis*cos(theta_e);
    }
    else
    {
        theta_e=SINGLEPI_CONSTANT/2;
        dis=50;
    }
    if(Left) theta=theta+theta_e;
    else     theta=theta-theta_e;
    return DPoint(Point.x_+dis*cos(theta),Point.y_+dis*sin(theta));


}

inline double
TangentAngle(DPoint Center, double radius, bool Left)
{
    double theta=atan2(Center.y_,Center.x_);
    double dis=sqrt(Center.x_*Center.x_+Center.y_*Center.y_);
    double theta_e;
    if(dis>radius)
        theta_e=asin(radius/dis);
    else
        theta_e=SINGLEPI_CONSTANT/2;
    if(Left) theta=theta+theta_e;
    else     theta=theta-theta_e;
    if(theta>SINGLEPI_CONSTANT)   theta=theta-2*SINGLEPI_CONSTANT;
    if(theta<-SINGLEPI_CONSTANT)  theta=theta+2*SINGLEPI_CONSTANT;
    return theta;
}


inline double
TangentAngle(DPoint Point,DPoint Center, double radius, bool Left)
{
    double theta=atan2(Center.y_-Point.y_,Center.x_-Point.x_);
    double dis=Dis_2P(Center,Point);
    double theta_e;
    if(dis>radius)
        theta_e=asin(radius/dis);
    else
        theta_e=SINGLEPI_CONSTANT/2;
    if(Left) theta=theta+theta_e;
    else     theta=theta-theta_e;
    if(theta>SINGLEPI_CONSTANT)   theta=theta-2*SINGLEPI_CONSTANT;
    if(theta<-SINGLEPI_CONSTANT)  theta=theta+2*SINGLEPI_CONSTANT;
    return theta;
}



inline DPoint
MidPointOf2Point(DPoint PointA,DPoint PointB)
{

    DPoint midpoint=DPoint((PointA.x_+PointB.x_)/2,(PointA.y_+PointB.y_)/2);
    return midpoint;
}


inline bool
VerticalPointOf2Point(DPoint &vertical, DPoint p, DPoint p1,DPoint p2)
{
    bool  flg = true;
    double k =0;
    double b = 0;

    if(p2.x_ - p1.x_ != 0)
    {
        k =  (p2.y_ - p1.y_)/(p2.x_ - p1.x_);
        b =  p2.y_ -  k*p2.x_;
        double   p2p1x = p2.x_-p1.x_;
        double   p2p1y = p2.y_-p1.y_;

        vertical.x_ =(p.x_*p2p1x+(p.y_-b)*p2p1y)/(p2p1x+k*p2p1y);
        vertical.y_ =  k*vertical.x_ + b;
        double  s1 = Dis_2P(p1,vertical);
        double  s2 = Dis_2P(p2,vertical);
        double  s = Dis_2P(p1,p2);
        if(   abs(s1+s2-s) <=1.0 )
        {
            flg = true;
        }
        else
        {
            flg = false;
        }
    }
    else
    {
        vertical.x_ = p2.x_;
        vertical.y_ =  p.y_;
        if( (vertical.y_-p2.y_)*(vertical.y_-p1.y_) <= 0 )
        {
            flg = true;
        }
        else
            flg =  false;
    }

    return flg;
}

inline int
Factorial(int n)
{
    int rtvl =  1;
    while(n != 0 )
    {
        rtvl = rtvl*n;
        n -=1;
    }
    return rtvl;

}

inline bool
MatrixInverse(double * M)
{
     double m11=*M;
     double m12=*(M+1);
     double m21=*(M+2);
     double m22=*(M+3);
     double value=m11*m22-m21*m12;
     if(value!=0)
     {
         *M    = m22/value;
         *(M+1)=-m12/value;
         *(M+2)=-m21/value;
         *(M+2)= m11/value;
         return true;
     }
     else
         return false;
}

inline void
MatrixMultify(double A[4][4], double B[4][4], double *C)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            *(C+4*i+j)=0;
            for(int l=0;l<4;l++)
                *(C+4*i+j)+=A[i][l]*B[l][j];
        }
    }

}

inline void
MatrixAdd(double A[4][4], double B[4][4], double *C)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            *(C+4*i+j)=A[i][j]+B[i][j];
        }
    }
}


inline void
MatrixTrans(double A[4][4], double *B)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            *(B+4*j+i)=A[i][j];
        }
    }

}

inline double
ThetaOf2Vector(DPoint V1, DPoint V2)
{

    if(sqrt(V1.x_*V1.x_+V1.y_*V1.y_)*sqrt(V2.x_*V2.x_+V2.y_*V2.y_)==0)//Ä³Ò»žöÎªÁã£¬·µ»ØSINGLEPI_CONSTANT
        return SINGLEPI_CONSTANT;
    else
        return acos((V1.x_*V2.x_+V1.y_*V2.y_)/(sqrt(V1.x_*V1.x_+V1.y_*V1.y_)*sqrt(V2.x_*V2.x_+V2.y_*V2.y_)));
}

inline int
DirOfPoint2Line(DPoint P, DPoint P1, DPoint P2)
{
    double theta=atan2(P.y_-P1.y_,P.x_-P1.x_)-atan2(P2.y_-P1.y_,P2.x_-P1.x_);
    if(theta>SINGLEPI_CONSTANT) theta=theta-2*SINGLEPI_CONSTANT;
    if(theta<=-SINGLEPI_CONSTANT) theta=theta+2*SINGLEPI_CONSTANT;
    if(theta>=0)
        return -1;
    else
        return 1;

}

inline double
AngleOf2Vector(DPoint P1, DPoint P2)
{
    double theta=atan2(P2.y_,P2.x_)-atan2(P1.y_,P1.x_);
    if(theta>SINGLEPI_CONSTANT) theta=theta-2*SINGLEPI_CONSTANT;
    if(theta<=-SINGLEPI_CONSTANT) theta=theta+2*SINGLEPI_CONSTANT;
    return theta;
}

inline DPoint
PointOfVertical(DPoint p1, DPoint p2, double x, double y)
{
    double len=sqrt(x*x+y*y);
    double t1=atan2(p2.y_-p1.y_,p2.x_-p1.x_);
    double t2=atan2(y,x);
    double t=t1+t2;
    return DPoint(len*cos(t)+p1.x_,len*sin(t)+p1.y_);

}



inline bool
CheckInAngle(double la, double ra, double ta, bool left)
{
    if(left)
    {
        if(la>ra)
        {
            if(la>ta && ta>ra )
                return false;
            else
                return true;
        }
        else
        {
            if(ta<=ra)
            {
                if(la>ta)
                    return false;
                else
                    return true;
            }
            else
                return false;
        }
    }
    else
    {
        if(la>ra)
        {
            if(la>ta && ta>ra )
                return false;
            else
                return true;
        }
        else
        {
            if(ta<=ra)
            {
                if(la>ta)
                    return false;
                else
                    return true;
            }
            else
                return true;
        }
    }
}

inline void
ClearUpAngle(double &angle)
{
    if(angle>SINGLEPI_CONSTANT)
        angle-=2*SINGLEPI_CONSTANT;
    if(angle<=-SINGLEPI_CONSTANT)
        angle+=2*SINGLEPI_CONSTANT;
}

inline DPoint
CoorInARef(DPoint P1, DPoint P2, DPoint O, DPoint P)
{
    DPoint temp=P-O;
    double theta=atan2(P2.y_-P1.y_,P2.x_-P1.x_);
    return DPoint(temp.x_*cos(theta)+temp.y_*sin(theta),temp.y_*cos(theta)-temp.x_*sin(theta));
}

inline DPoint
ConCoorInARef(DPoint P1, DPoint P2, DPoint O, DPoint P)
{
    double theta=atan2(P2.y_-P1.y_,P2.x_-P1.x_);
    DPoint temp=DPoint(P.x_*cos(theta)-P.y_*sin(theta),P.x_*sin(theta)+P.y_*cos(theta));
    return (temp+O);

}
inline bool
RelCorIsValid(DPoint P)
{
    if(P.x_!=0 || P.y_!=0)
        return true;
    else
        return false;
}


inline DPoint
P2RotateWithP1(DPoint P1, DPoint P2, double theta)
{
  DPoint P3;
  double dx=P2.x_-P1.x_;
  double dy=P2.y_-P1.y_;
    P3.x_=P1.x_+(dx*cos(theta)-dy*sin(theta));
    P3.y_=P1.y_+(dx*sin(theta)+dy*cos(theta));
    return P3;
}

inline bool
VectorEqu(DPoint P1, DPoint P2)
{
    double e=LOCATION_ERROR*4;
    double dis=(P1.x_-P2.x_)*(P1.x_-P2.x_)+(P1.y_-P2.y_)*(P1.y_-P2.y_);
    if(dis>e*e)
        return 0;
    else
        return 1;
}

inline bool VectorEqu(DPoint P1, DPoint P2,double e)
{
    double dis=(P1.x_-P2.x_)*(P1.x_-P2.x_)+(P1.y_-P2.y_)*(P1.y_-P2.y_);
    if(dis>e*e)
        return 0;
    else
        return 1;
}

inline void ExchangeSort(float* pData,char Count,char order[])
{
    int iTemp,otemp;
    for(int i=0;i<Count-1;i++)
    {
        for(int j=i+1;j<Count;j++)
        {
            if(pData[j]>pData[i])
            {
                iTemp = pData[i];
                pData[i] = pData[j];
                pData[j] = iTemp;

                otemp=order[i];
                order[i]=order[j];
                order[j]=otemp;
            }
        }
    }
}

inline DPoint
DIsPointInAB2C(DPoint PointA,DPoint PointB,DPoint PointC,double dis,double e,int Maxtime)
{
  DPoint MidPoint=MidPointOf2Point(PointA,PointB);
  double disc2mid=Dis_2P(PointC,MidPoint);
  int time=0;
  while (dis<e||time>Maxtime)
  {
       time++;
       if(disc2mid>dis)
       {
           PointB=MidPoint;

       }
       else
       {
          PointA=MidPoint;
       }
       MidPoint=MidPointOf2Point(PointA,PointB);
       disc2mid=Dis_2P(PointC,MidPoint);
  }
  return MidPoint;

}

inline double
Product(DPoint P1,DPoint P2,DPoint P3)
{
    return(P2.x_-P1.x_)*(P3.y_-P1.y_)-(P3.x_-P1.x_)*(P2.y_-P1.y_);
}
inline bool
IsInTriangle(DPoint P1,DPoint P2,DPoint P3,DPoint P4)
{
    if(Product(P1,P2,P4)>=0&&Product(P2,P3,P4)>=0&&Product(P3,P1,P4)>=0)
    {
        return true;
    }
    return false;
}


inline bool
IsInRectangle(DPoint P1,DPoint P2,DPoint P3,DPoint P4,DPoint P5)
{
    if(Product(P1,P2,P5)>=0&&Product(P2,P3,P5)>=0&&Product(P3,P4,P5)>=0&&Product(P4,P1,P5)>=0)
    {
        return true;
    }
    return false;
}

inline float
uf(float x,float a,float  b,float c)
{
if(x<=a)
return 0;
else if((a<x)&&(x<=b))
return  (x-a)/(b-a);
else if((b<x)&&(x<=c))
return (c-x)/(c-b);
else if(x>c)
return 0;
}

inline float
cuf(float x,float a,float b,float c)
{   float y,z;
    z=(b-a)*x+a;
    y=c-(c-b)*x;
    return (y+z)/2;
}

inline float
ufl(float x,float a,float b)
{
    if(x<=a)
    return 1;
    else if((a<x)&&(x<=b))
    return (b-x)/(b-a);
    else if(x>b)
    return 0;
}

inline float
cufl(float x,float a,float b)
{

    return b-(b-a)*x;
}

inline float
ufr(float x,float a,float b)
{
if(x<=a)
return 0;
if((a<x)&&(x<b))
return (x-a)/(b-a);
if(x>=b)
return 1;
}

inline float
cufr(float x,float a,float b)
{
return (b-a)*x+a;
}

inline float
fand(float a,float b)
{
    return (a<b)?a:b;
}

inline float
forr(float a,float b)
{
    return (a<b)?b:a;
}

#endif // COMMON_H

