#ifndef LINE_HPP
#define LINE_HPP

#include "PPoint.hpp"
#include <cmath>

const double eps=1e-5;    // 计算精度
class Line_
{

public:
	// various constructors
	Line_();
	Line_(const Line_ & line);
	//!  general form of line
	Line_(double a,double b,double c);
	//!  line from slope k and intercept n
	Line_(double k,double b);
	//!  line from two points
	template<typename _Tp>  Line_(const DPoint_<_Tp> & pt1,const DPoint_<_Tp> & pt2);
	//!  line from slope k and a point
	template<typename _Tp>  Line_(double k,const DPoint_<_Tp> & pt);


	//!  whether the line is parallel
	bool isParallel(const Line_ & line) const;
	//!  whether the line is orthogonal 
	bool isOrthogonal (const Line_ & line) const;
	//!  the distance between a point and a line;
	template<typename _Tp> double distance(const DPoint_<_Tp> & pt) const ;
	//!  the distance between two parallel lines
	double distance(const Line_ & line) const ;
    //!  the cross point of two lines; if success, return 1, otherwise return 0
    bool crosspoint(const Line_ & line, DPoint_<double> &pt) const;

	double A_,B_,C_;  //< general form: Ax+By+C=0;
	double k_,b_;     //< slope and intercept form:Ax+By+C=0	    
	bool   isSlope_;  //< whether the slope is exist;
	bool   isLine_;   //< whether it is a line or not;
};


//////////////////////////////// Line ////////////////////////////////
inline Line_::Line_() : A_(0.),B_(0.),C_(0.),k_(0.),b_(0.),isSlope_(false),isLine_(false) {}
inline Line_::Line_(const Line_ & line) : A_(line.A_),B_(line.B_),C_(line.C_),
	k_(line.k_),b_(line.b_),isSlope_(line.isSlope_),isLine_(line.isLine_) {}
inline Line_::Line_(double a,double b,double c) : A_(a),B_(b),C_(c),isLine_(a!=0||b!=0)
{
	if(B_!=0)
	{
		isSlope_=true;
		k_=-A_/B_;
		b_=-C_/B_;
	}
	else
	{
		k_=0;
		b_=0;
		isSlope_=false;
	}
}
inline Line_::Line_(double k,double b) : A_(k),B_(-1),C_(b),k_(k),b_(b),isSlope_(true),isLine_(true) {}
template<typename _Tp> inline Line_::Line_(const DPoint_<_Tp> & pt1,const DPoint_<_Tp> & pt2)
{
	if(pt1!=pt2)
	{
		isLine_=true;
        if(pt1.x_!=pt2.x_)  /** pt2可以认为是向两的终点，pt1位起点，atan2(A_,-B) = atan2(k_)与向两(pt2.x_-pt1.x_,pt2.y_-pt1.y_)相同*/
		{
			k_=double(pt2.y_-pt1.y_)/double(pt2.x_-pt1.x_);
			b_=double(pt1.y_*pt2.x_-pt2.y_*pt1.x_)/double(pt2.x_-pt1.x_);
			A_=k_;
			B_=-1.0;
			C_=b_;
			isSlope_=true;
		}
        else
		{
            /** pt2可以认为是向两的终点，pt1位起点，atan2(A_,-B) 与向两(pt2.x_-pt1.x_,pt2.y_-pt1.y_)相同*/
            A_=1.0;
            if((pt2.y_-pt1.y_)<0)
              A_=-1.0;
			B_=0.0;
            C_=-1.0*A_*pt1.x_;

            /** 没有斜率 */
			k_=0;
			b_=0;
			isSlope_=false;
		}
	}
	else
	{
		A_=0;B_=0;C_=0;k_=0;b_=0;
		isLine_=false;
		isSlope_=false;
	}
}
template<typename _Tp> inline  Line_::Line_(double k,const DPoint_<_Tp> & pt)
{
	k_ = k;
	b_ = double(pt.y_-k*pt.x_);
	A_ = k;
	B_ = -1.0;
	C_ = b_;
	isLine_=true;
	isSlope_=true;
}
inline bool Line_::isParallel(const Line_ & line) const
{
	if(isLine_&&line.isLine_)
		return((line.A_*B_-A_*line.B_)==0);
	else
		return (false);
}
inline bool Line_::isOrthogonal(const Line_ & line) const
{
	if(isLine_&&line.isLine_)
		return((A_*line.A_+B_*line.B_)==0);
	else
		return (false);
}

template<typename _Tp> inline double Line_::distance(const DPoint_<_Tp> & pt) const 
{
	return (std::abs(A_*pt.x_+B_*pt.y_+C_)/sqrt(A_*A_+B_*B_));
}
inline double Line_::distance(const Line_ & line) const
{
	if(isParallel(line))
		return (std::abs(C_-line.C_)/sqrt(A_*A_+B_*B_));
	else
		return (0.0);
}
inline bool Line_::crosspoint(const Line_ & line, DPoint_<double> &pt) const
{
	double ycoef=double(A_*line.B_-line.A_*B_);
	if(isLine_&&line.isLine_&&ycoef!=0)
	{
		pt.x_=double(B_*line.C_-line.B_*C_)/ycoef;
		pt.y_=double(-A_*line.C_+line.A_*C_)/ycoef;

        return 1;
	}
    else
        return 0;
}
//!  get the  vertical line which passes through point pt;  
template<typename _Tp> static inline Line_ verticalline(const Line_ & line,const DPoint_<_Tp> & pt) 
{
	if(line.isLine_)
	{
		if(line.isSlope_)
		{
			if(line.k_==0)
				return Line_(1,0,-pt.x_);
			else
				return Line_(-1.0/line.k_,pt);
		}  
		else
			return Line_(0.0,pt.y_);
	}
	else
		return Line_();
}
//! get the point which has the dis with pt in line 
template<typename _Tp> static inline DPoint_<_Tp> pointinline(const Line_ & line , const DPoint_<_Tp> & pt,double dis)
{
	double theta=atan2(line.A_,-line.B_);
	return DPoint_<_Tp>(_Tp(pt.x_+dis*cos(theta)),_Tp(pt.y_+dis*sin(theta)));
}

//! get the vertical point which is in the line, and the new line connects the vertical point 
//! and input point pt is vertical with original line
template<typename _Tp> static inline DPoint_<_Tp> verticalpoint(const Line_ & line , const DPoint_<_Tp> & pt)
{
	DPoint_<double> outpt=DPoint_<double>(0.0,0.0);
	if(line.isLine_)
	{
		Line_ vertical_line=verticalline(line,pt);
        line.crosspoint(vertical_line, outpt);
	}
	return outpt;
}


/** 线段，起点终点*/
class LineSegment
{
public:
    enum {
      StartLeft = 0,
      BetweenStartAndEnd = 1,
      EndPtRight = 2
    };

public:
    LineSegment(){
      vector_=end_=start_=DPoint(0,0);
    }
    LineSegment(const DPoint & _start, const DPoint & _end){
       start_ =_start;
       end_   =_end;
       vector_=end_-start_;
    }
    LineSegment(const LineSegment & _lineSement){
        start_ =_lineSement.start_;
        end_   =_lineSement.end_;
        vector_=_lineSement.vector_;
    }

    /** 点与线段的距离*/
    double distance(const DPoint & pt,bool isBetween = false) const
    {
        DPoint vector_vp = pt- start_;
        double dotProduct = vector_vp.x_*vector_.x_ + vector_vp.y_ *vector_.y_;
        double LineSegLength = vector_.norm() * vector_.norm();
        double distance = 0;
        if(dotProduct <= 0)     //小于零，表示vector_vp 与 vector_反向，点在开始点一边
        {
           if(!isBetween)
              distance = pt.distance(start_);
           else
               distance=100;
        }
        else if (dotProduct >= LineSegLength) //大于线段长度，表示vector_vp 与 vector_同向，点在末尾点一边
        {
           if(!isBetween)
              distance = pt.distance(end_);
           else
               distance=100;
        }
        else  //点的有一个坐标分量在线段之间
        {
           double r = dotProduct / LineSegLength;
           DPoint vert_pt = start_ + r *vector_;
           distance = pt.distance(vert_pt);
        }
        return distance;
    }

    double distance() const {
      return vector_.norm();
    }

    bool crosspoint(LineSegment ls, DPoint& lscp)
    {
        Line_ l1(start_, end_), l2(ls.start_, ls.end_);
        DPoint fin_pt=lscp;     // 保证如果lscp得不到，那么它不会变，变的是fin_pt
        if( l1.crosspoint(l2, fin_pt) )
        {
            if(isInLineSegment(fin_pt) && ls.isInLineSegment(fin_pt) )
            {
                lscp = fin_pt;
                return 1;
            }
            else
                return 0;
        }
        else
            return 0;
    }

    bool isInLineSegment(DPoint pt)
    {
        DPoint vec1 = start_ - pt, vec2 = pt - end_;
        double  re = vec1.dot(vec2)/(vec1.norm()*vec2.norm());
        if( fabs(re - 1.0) < eps)
            return 1;
        else
            return 0;
    }
    int  decideWhere(const DPoint & pt)
    {

        DPoint vector_vp = pt- start_;
        double dotProduct = vector_vp.x_*vector_.x_ + vector_vp.y_ *vector_.y_;
        double LineSegLength = vector_.norm() * vector_.norm();
        if(dotProduct < 0)     //小于零，表示vector_vp 与 vector_反向，点在开始点一边
            return StartLeft;
        else if (dotProduct > LineSegLength) //大于线段长度，表示vector_vp 与 vector_同向，点在末尾点一边
            return EndPtRight;
        else  //点的有一个坐标分量在线段之间
            return  BetweenStartAndEnd;
    }

public:
    DPoint start_;     /** 线段的起始点*/
    DPoint end_;       /** 线段的终点*/
    DPoint vector_;    /** 线段的终点减去起点的向量*/
};

#endif //LINE_HPP
