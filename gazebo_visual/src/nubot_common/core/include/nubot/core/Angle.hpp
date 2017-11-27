#ifndef __NUBOT_CORE_ANGLE_HPP__
#define __NUBOT_CORE_ANGLE_HPP__

#include <cmath>
#include <vector>

const double DOUBLEPI_CONSTANT       = 6.283185307179586232;
const double SINGLEPI_CONSTANT       = 3.14159265358979323846;
const double RADIAN2DEGREE_CONSTANT  = 57.295779513082322865;
const double DEGREE2RADIAN_CONSTANT  = 0.017453292519943295474;

namespace nubot
{

class Angle 
{

public:
	//! various constructors
	Angle ();
	Angle (double a) ; 
	Angle (double a,bool israd) ;
	Angle (const Angle& a) ;
	const Angle & operator = (const Angle& a);
	//! conversion to (-pi,pi]
	void   setAngle (const double & ) ;
	//! conversion to degree(-180,180]
	int    degree();
	//! conversion to (-pi,pi] from degree;
	double radian(int _degree);

	bool in_between(const Angle a, const Angle b);
    double Angsin();
    double Angcos();
    double radian_;
};
 
/////////////////////Angle operation///////////////////////
inline Angle::Angle () : radian_(0) {
};
inline Angle::Angle (double a) 
{ setAngle (a);}
inline Angle::Angle (double a ,bool israd) 
{
	if(israd)
		setAngle (a);
	else
		setAngle(a*DEGREE2RADIAN_CONSTANT);
}
inline bool
Angle::in_between (const Angle a, const Angle b) 
{
	if (b.radian_>=a.radian_)
		return (a.radian_<=radian_) && (radian_<=b.radian_);
	else
		return (a.radian_<=radian_) || (radian_<=b.radian_);
}
inline Angle::Angle (const Angle& a) : radian_(a.radian_) {
}

inline const Angle& Angle::operator= (const Angle& a)
{ radian_=a.radian_; return *this; }

inline void Angle::setAngle(const double & a)
{
	if (a<-SINGLEPI_CONSTANT) {
		int k =int(ceil (-a/(SINGLEPI_CONSTANT)));
		radian_ = a+(k/2)*DOUBLEPI_CONSTANT;
		return ;
	}
	if (a>=SINGLEPI_CONSTANT) {
		int k = int(ceil (a/(SINGLEPI_CONSTANT)));
		radian_ = a-(k/2)*DOUBLEPI_CONSTANT;
		return ;
	}
	radian_=a;
}
inline int Angle::degree(){
	return (int(radian_*RADIAN2DEGREE_CONSTANT));  
}

inline double Angle::Angsin(){
    return sin(radian_);
}
inline double Angle::Angcos(){
    return cos(radian_);
}

inline double Angle::radian(int _degree)
{ return Angle(_degree*DEGREE2RADIAN_CONSTANT).radian_; }
static inline Angle operator - (const Angle& a)
{ return Angle(-a.radian_);}
static inline bool operator == (const Angle& a, const Angle& b)
{ return a.radian_==b.radian_; } 

static inline bool operator != (const Angle& a, const Angle& b)
{ return a.radian_!=b.radian_; }
static inline  Angle operator +  (const Angle & a, const Angle & b) {
	return Angle(double(a.radian_+b.radian_));
}	
static inline  Angle operator - (const Angle & a, const Angle & b)  {		
	return Angle(double(a.radian_-b.radian_));
}
static inline Angle & operator += (Angle& a, Angle & b){
	a=Angle(a.radian_+b.radian_);
	return a;
}
static inline Angle & operator -= (Angle& a, Angle&  b){
	a=Angle(a.radian_-b.radian_);
	return a;
}	
template<typename _Tp> static inline Angle & operator += (Angle& a, _Tp b){
	a=Angle(a.radian_+b);
	return a;
}	
template<typename _Tp> static inline Angle & operator -= (Angle& a , _Tp b)
{
	a=Angle(a.radian_-b);
	return a;
}	
template<typename _Tp> static inline Angle & operator /= (Angle& a , _Tp b){
	a=Angle(a.radian_/b);
	return a;
}	
template<typename _Tp> static inline Angle & operator *= (Angle& a , _Tp b){
	a=Angle(a.radian_*b);
	return a;
}
template<typename _Tp> static inline Angle operator +  (const Angle & a , const _Tp & b){
	return Angle(double(a.radian_+b));
}	
template<typename _Tp> static inline Angle operator - (const Angle & a , const _Tp & b){
	return Angle(double(a.radian_-b));
}	
template<typename _Tp> static inline Angle operator * (const _Tp &a , const Angle & b){ 
	return Angle(double(a*b.radian_));
}
template<typename _Tp> static inline Angle operator * (const Angle & a , const _Tp & b ){
	return Angle(double(a.radian_*b));
}
inline double Angsin(const Angle & a){
    return sin(a.radian_);
}
inline double Angcos(const Angle & a){
    return cos(a.radian_);
}
}

#endif  //!__NUBOT_CORE_ANGLE_HPP__
