#ifndef __NUBOT_CORE_CIRCLE_HPP__
#define __NUBOT_CORE_CIRCLE_HPP__

#include "Line.hpp"
#include <cmath>
#include <vector>

namespace nubot
{
using std::vector;

class Circle
{

public:
	// various constructors
	Circle();
	template<typename _Tp> Circle(double _radius, const DPoint_<_Tp> & _center);
	Circle(const Circle & _circle);
	//! two points are endpoints of a diameter 
	template<typename _Tp>  Circle(const DPoint_<_Tp> & pt1, const DPoint_<_Tp> & pt2);

	//!  whether the point is in the circle 
	template<typename _Tp> bool inside(const DPoint_<_Tp> & pt) const;
	//!  whether the point is on the circle 
	template<typename _Tp> bool onedge(const DPoint_<_Tp> & pt) const;
	//!  crossing point between line and circle
	std::vector< DPoint_<double> > crosspoint(const Line_ & line) const;
	//!  tangent point of circle and tangential line pass through pt and  tangent point
	template<typename _Tp> std::vector< DPoint_<double> > tangentpoint(const DPoint_<_Tp> & pt) const;
    
	//! the relationship between Line and Circle;
 	bool isIntersect(const Line_ & line) const;
	bool isContact (const Line_ & line)  const;
	bool isSeparate (const Line_ & line) const;

	double radius_;          //<radius of circle
	DPoint_<double> center_; //<center of circle
};


//////////////////////////////// Circle ////////////////////////////////
inline Circle::Circle() : radius_(0.0),center_(DPoint_<double>(0.0,0.0)) {};
template<typename _Tp> inline Circle::Circle(double _radius, const DPoint_<_Tp> & _center) : radius_(_radius),center_(_center)  {};
inline Circle::Circle(const Circle & _circle) : radius_(_circle.radius_),center_(_circle.center_) {};
template<typename _Tp> inline Circle::Circle( const DPoint_<_Tp> & pt1, const DPoint_<_Tp> & pt2)
{
	radius_=pt1.distance(pt2)/2.0;
	center_=(DPoint2d(pt1)+DPoint2d(pt2))*(1/2.0);
}
template<typename _Tp> inline bool Circle::inside(const DPoint_<_Tp> & pt) const
{
	return(center_.distance(pt)<radius_);
}
template<typename _Tp> inline bool Circle::onedge(const DPoint_<_Tp> & pt) const
{
	return(center_.distance(pt)==radius_);
}
inline bool Circle:: isIntersect(const Line_ & line) const
{
	return (line.distance(center_)<radius_);
}
inline bool Circle:: isContact (const Line_ & line) const
{
	return (line.distance(center_)==radius_);
}
inline bool Circle:: isSeparate (const Line_ & line) const
{
	return (line.distance(center_)>radius_);
}


inline std::vector< DPoint_<double> > Circle::crosspoint(const Line_ & line) const
{
	vector< DPoint_<double> > cross_point;
	cross_point.reserve(2);
	double  disLine=line.distance(center_);
	//! two or one intersection points
	if(disLine<=radius_)
	 {
	    if(disLine<radius_) 
	    {
                DPoint2d pt=verticalpoint(line,center_);
		double tmpdis=DPoint2d(pt-center_).norm();
		double dis=sqrt(radius_*radius_-tmpdis*tmpdis);
		cross_point.push_back(pointinline(line,pt,dis));
		cross_point.push_back(pointinline(line,pt,-dis)); 
	    }
	    else
	       cross_point.push_back(verticalpoint(line,center_)); 
	 }		
	return cross_point;
}

template<typename _Tp> inline std::vector< DPoint_<double> > Circle::tangentpoint(const DPoint_<_Tp> & pt) const
{
	vector< DPoint_<double> > tangent_point;
	double dispt=center_.distance(pt);
	if(dispt>=radius_)
	{
		if(dispt>radius_)
		{		
			DPoint2d Vect=center_-DPoint2d(pt);
		        Angle theta=Vect.angle();
		        Angle theta_e=Angle(asin(radius_/dispt));
		        double dis=dispt*cos(theta_e.radian_);
			Angle tmp=theta+theta_e;
			tangent_point.push_back(DPoint2d(pt)+DPoint2d(dis*cos(tmp.radian_),dis*sin(tmp.radian_)));  
			tmp = theta-theta_e;
			tangent_point.push_back(DPoint2d(pt)+DPoint2d(dis*cos(tmp.radian_),dis*sin(tmp.radian_)));
		}
		else
		   tangent_point.push_back(DPoint2d(pt)); 

	}
	return tangent_point;
}


}
#endif //! __NUBOT_CORE_CIRCLE_HPP__
