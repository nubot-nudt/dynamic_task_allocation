
#ifndef __NUBOT_CORE_DPOINT_HPP__
#define __NUBOT_CORE_DPOINT_HPP__

#include "Angle.hpp"
#include <cmath>

namespace nubot
{
	
template<typename _Tp> class DPoint_
{
public:
	typedef _Tp value_type;
	// various constructors
	DPoint_();
	template<typename _Tp2> DPoint_(_Tp2 _x, _Tp2 _y);
	template<typename _Tp2> DPoint_(const DPoint_<_Tp2>& pt);

	template<typename _Tp2> DPoint_& operator = (const DPoint_<_Tp2>& pt);
	//! conversion to another data type
	template<typename _Tp2> operator DPoint_<_Tp2>() const;
	//! Polar point is converted to DPont;
	template<typename _Tp2> DPoint_(const _Tp2 & pt); 
	// 	//! Polar point is converted to DPont;
	template<typename _Tp2> DPoint_<_Tp> & operator = (const _Tp2 & pt);
	//! dot product
	_Tp dot(const DPoint_& pt) const;
	//! dot product computed in double-precision arithmetics
	double ddot(const DPoint_& pt) const;
	//! cross-product
	double cross(const DPoint_& pt) const;
	//! distance between (x_,y_) and pt
	template<typename _Tp2> double distance(const DPoint_<_Tp2>& pt) const;
	//! value of norm;
	double norm() const;
	//! angle of (y_,x_)
	Angle  angle() const;	
	//! angle of (y_-pt.y_,x_-pt.x_)
	template<typename _Tp2> Angle angle(const DPoint_<_Tp2>& pt) const; 
	//!  transfered into  (-x_,-y_)
	DPoint_<_Tp>  mirror() const;
	//!  rotate angle around original point (0,0)
	DPoint_<_Tp>  rotate (const Angle & _angle) const ;
	//!  rotate angle around pt
	template<typename _Tp2> DPoint_<_Tp> rotate(const DPoint_<_Tp2>& pt,const Angle & _angle) const;
    //!
    template<typename _Tp2> DPoint_<_Tp>  pointofline(const DPoint_<_Tp2>& pt,const double & _distance) const;

    _Tp x_, y_; //< the point coordinates
};

typedef DPoint_<int>    DPoint2i;
typedef DPoint_<float>  DPoint2f;
typedef DPoint_<double> DPoint2d;
typedef DPoint2d DPoint;

//////////////////////////////// Cartesian  Point ////////////////////////////////
template<typename _Tp> inline DPoint_<_Tp>::DPoint_() : x_(0), y_(0) {}
template<typename _Tp> template<typename _Tp2> inline DPoint_<_Tp>::DPoint_(_Tp2 _x, _Tp2 _y) : x_(_Tp(_x)), y_(_Tp(_y)) {}
template<typename _Tp> template<typename _Tp2> inline DPoint_<_Tp>::DPoint_(const DPoint_<_Tp2>& pt)
	: x_(_Tp(pt.x_)), y_(_Tp(pt.y_)) {}
template<typename _Tp> template<typename _Tp2> inline DPoint_<_Tp>& DPoint_<_Tp>::operator = (const DPoint_<_Tp2>& pt)
{ x_ =_Tp(pt.x_); y_ = _Tp(pt.y_); return *this; }
template<typename _Tp> template<typename _Tp2> inline DPoint_<_Tp>::operator DPoint_<_Tp2>() const
{ return DPoint_<_Tp>(_Tp(x_), _Tp(y_)); }

template<typename _Tp> template<typename _Tp2> inline DPoint_<_Tp>::DPoint_(const _Tp2 & pt)
	: x_(_Tp(pt.radius_*cos(pt.angle_.radian_))),y_(_Tp(pt.radius_*sin(pt.angle_.radian_))) {}

template<typename _Tp> template<typename _Tp2> inline DPoint_<_Tp>& DPoint_<_Tp>::operator = (const _Tp2 & pt)
{
	x_=_Tp(pt.radius_*cos(pt.angle_.radian_));
	y_=_Tp(pt.radius_*sin(pt.angle_.radian_));
	return *this;
}

template<typename _Tp> inline _Tp DPoint_<_Tp>::dot(const DPoint_& pt) const
{ return _Tp(x_*pt.x_ + y_*pt.y_); }
template<typename _Tp> inline double DPoint_<_Tp>::ddot(const DPoint_& pt) const
{ return (double)x_*pt.x_ + (double)y_*pt.y_; }
template<typename _Tp> inline double DPoint_<_Tp>::cross(const DPoint_& pt) const
{ return (double)x_*pt.y_ - (double)y_*pt.x_; }
template<typename _Tp> inline DPoint_<_Tp> DPoint_<_Tp>::rotate( const Angle & _angle)  const
{   return DPoint_<_Tp>(_Tp(x_*cos(_angle.radian_)+y_*sin((_angle.radian_))),
                        _Tp(-x_*sin(_angle.radian_)+y_*cos(_angle.radian_))); }

template<typename _Tp> template<typename _Tp2>inline double DPoint_<_Tp>::distance(const DPoint_<_Tp2> & pt) const
{
	return (std::sqrt(double((x_-pt.x_)*(x_-pt.x_)+(y_-pt.y_)*(y_-pt.y_))));
}

template<typename _Tp> template<typename _Tp2>inline DPoint_<_Tp> DPoint_<_Tp>::rotate(const DPoint_<_Tp2> & pt,const Angle & _angle) const
{
	Angle  theta =_angle+(atan2(double(y_-pt.y_),double(x_-pt.x_)));
	double tmp_dis=distance(pt);
	return DPoint_<_Tp>(_Tp(pt.x_+cos(theta.radian_)*tmp_dis),_Tp(pt.y_+sin(theta.radian_)*tmp_dis));
}

template<typename _Tp> template<typename _Tp2>inline DPoint_<_Tp> DPoint_<_Tp>::pointofline(const DPoint_<_Tp2>& pt,const double & _distance) const
{
    Angle theta =atan2(double(pt.y_-y_),double(pt.x_-x_));
    return DPoint_<_Tp>(_Tp(x_+cos(theta.radian_)*_distance),_Tp(y_+sin(theta.radian_)*_distance));
}

template<typename _Tp>inline double DPoint_<_Tp>::norm() const
{
	return std::sqrt((double)x_*x_ + (double)y_*y_);
}
template<typename _Tp> inline Angle DPoint_<_Tp>::angle() const
{ 
	return Angle(atan2(y_,x_));
}
template<typename _Tp> template<typename _Tp2> Angle DPoint_<_Tp>::angle(const DPoint_<_Tp2>& pt) const
{
	return Angle(atan2(double(y_-pt.y_),double(x_-pt.x_)));
}

template<typename _Tp> inline DPoint_<_Tp> DPoint_<_Tp>::mirror()  const
{   return DPoint_<_Tp>(_Tp(-x_),_Tp(-y_)); }

template<typename _Tp> static inline DPoint_<_Tp>& operator += (DPoint_<_Tp>& a, const DPoint_<_Tp>& b)
{
	a.x_ = _Tp(a.x_ + b.x_);
	a.y_ = _Tp(a.y_ + b.y_);
	return a;
}

template<typename _Tp> static inline DPoint_<_Tp>& operator -= (DPoint_<_Tp>& a, const DPoint_<_Tp>& b)
{
	a.x_ = _Tp(a.x_ - b.x_);
	a.y_ = _Tp(a.y_ - b.y_);
	return a;
}

template<typename _Tp> static inline DPoint_<_Tp>& operator *= (DPoint_<_Tp>& a, int b)
{
	a.x_ = _Tp(a.x_*b);
	a.y_ = _Tp(a.y_*b);
	return a;
}

template<typename _Tp> static inline DPoint_<_Tp>& operator *= (DPoint_<_Tp>& a, float b)
{
	a.x_ = _Tp(a.x_*b);
	a.y_ = _Tp(a.y_*b);
	return a;
}

template<typename _Tp> static inline DPoint_<_Tp>& operator *= (DPoint_<_Tp>& a, double b)
{
	a.x_ = _Tp(a.x_*b);
	a.y_ = _Tp(a.y_*b);
	return a;
}

template<typename _Tp> static inline bool operator == (const DPoint_<_Tp>& a, const DPoint_<_Tp>& b)
{ return a.x_ == b.x_ && a.y_ == b.y_; }

template<typename _Tp> static inline bool operator != (const DPoint_<_Tp>& a, const DPoint_<_Tp>& b)
{ return a.x_ != b.x_ || a.y_ != b.y_; }

template<typename _Tp> static inline DPoint_<_Tp> operator + (const DPoint_<_Tp>& a, const DPoint_<_Tp>& b)
{ return DPoint_<_Tp>( _Tp(a.x_ + b.x_), _Tp(a.y_ + b.y_) ); }

template<typename _Tp> static inline DPoint_<_Tp> operator - (const DPoint_<_Tp>& a, const DPoint_<_Tp>& b)
{ return DPoint_<_Tp>( _Tp(a.x_ - b.x_), _Tp(a.y_ - b.y_) ); }

template<typename _Tp> static inline DPoint_<_Tp> operator - (const DPoint_<_Tp>& a)
{ return DPoint_<_Tp>( _Tp(-a.x_), _Tp(-a.y_) ); }

template<typename _Tp> static inline DPoint_<_Tp> operator * (const DPoint_<_Tp>& a, int b)
{ return DPoint_<_Tp>( _Tp(a.x_*b), _Tp(a.y_*b) ); }

template<typename _Tp> static inline DPoint_<_Tp> operator * (int a, const DPoint_<_Tp>& b)
{ return DPoint_<_Tp>( _Tp(b.x_*a), _Tp(b.y_*a) ); }

template<typename _Tp> static inline DPoint_<_Tp> operator * (const DPoint_<_Tp>& a, float b)
{ return DPoint_<_Tp>( _Tp(a.x_*b), _Tp(a.y_*b) ); }

template<typename _Tp> static inline DPoint_<_Tp> operator * (float a, const DPoint_<_Tp>& b)
{ return DPoint_<_Tp>( _Tp(b.x_*a), _Tp(b.y_*a) ); }

template<typename _Tp> static inline DPoint_<_Tp> operator * (const DPoint_<_Tp>& a, double b)
{ return DPoint_<_Tp>( _Tp(a.x_*b), _Tp(a.y_*b) ); }

template<typename _Tp> static inline DPoint_<_Tp> operator * (double a, const DPoint_<_Tp>& b)
{ return DPoint_<_Tp>( _Tp(b.x_*a), _Tp(b.y_*a) ); }

}

#endif //!__DPOINT_H_
