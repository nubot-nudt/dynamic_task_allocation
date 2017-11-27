#ifndef __NUBOT_CORE_PPOINT_HPP__
#define __NUBOT_CORE_PPOINT_HPP__

#include "DPoint.hpp"
#include <cmath>

namespace nubot
{

template<typename _Tp> class PPoint_
{
public:
	// various constructors
	PPoint_();
	template<typename _Tp2> PPoint_(Angle  _angle, _Tp2 _radius);
	PPoint_(const PPoint_& pt);

	//! DPoint is converted to PPoint_;
	template<typename _Tp2> PPoint_(const DPoint_<_Tp2> & pt); 
	//! DPoint is converted to PPoint_;
	template<typename _Tp2> PPoint_<_Tp> & operator = (const DPoint_<_Tp2> & pt) const;

	//! rotate angle ;
	PPoint_<_Tp>  rotate (const Angle & _angle) const ;

	Angle angle_;   //< angle
	_Tp radius_;    //< radius 
};

typedef PPoint_<int>    PPoint2i;
typedef PPoint_<float>  PPoint2f;
typedef PPoint_<double> PPoint2d;
typedef PPoint2d PPoint;

//////////////////////////////// Polar Point ////////////////////////////////
template<typename _Tp>  inline PPoint_<_Tp>::PPoint_() : angle_(0), radius_(0) {}
template<typename _Tp>  template<typename _Tp2> inline PPoint_<_Tp>::PPoint_(Angle _angle, _Tp2 _radius) 
	: angle_(_angle),   radius_(_Tp(_radius)) {}
template<typename _Tp>  inline PPoint_<_Tp>::PPoint_(const PPoint_& pt) 
	: angle_(pt.angle_), radius_(pt.radius_) {}

template<typename _Tp>  template<typename _Tp2> inline PPoint_<_Tp>::PPoint_(const DPoint_<_Tp2> & pt)
	:angle_(atan2((double)pt.y_,(double)pt.x_)),radius_(_Tp(hypot(pt.x_,pt.y_))) {}

template<typename _Tp> template<typename _Tp2> inline PPoint_<_Tp>& PPoint_<_Tp>::operator = (const DPoint_<_Tp2> & pt) const
{
	angle_=Angle(atan2((double)pt.y_,(double)pt.x_));
	radius_=_Tp(hypot(pt.x_,pt.y_));
	return *this;
}
template<typename _Tp> static inline bool operator == (const PPoint_<_Tp>& a, const PPoint_<_Tp>& b)
{ return a.angle_ == b.angle_ && a.radius_ == b.radius_; }

template<typename _Tp> static inline bool operator != (const PPoint_<_Tp>& a, const PPoint_<_Tp>& b)
{ return a.angle_ != b.angle_ || a.radius_ != b.radius_; }

template<typename _Tp> inline PPoint_<_Tp> PPoint_<_Tp>::rotate (const Angle & _angle) const 
{
	return PPoint_<_Tp>(Angle(angle_+_angle),radius_);
}

}
#endif //! __PPOINT_HPP_
