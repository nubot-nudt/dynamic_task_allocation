
#ifndef NUBOT_TIME_HPP_
#define NUBOT_TIME_HPP_

#include <iostream>
#include <sys/time.h>

// gets the code from tribots

namespace nubot {

class Time {

public:
    /*! @brief  various constructors;*/
    Time () throw ();
    Time (const Time&) throw ();
    Time (const timeval&) throw ();
    const Time& operator= (const Time&) throw ();


    /*! @brief  get the microsecond ;*/
    long int get_usec () const throw ();
    /*! @brief  get the millisecond ;*/
    long int get_msec () const throw ();
    /*! @brief  get the second ;*/
    long int get_sec () const throw ();

    /*! @brief  set the microsecond ;*/
    void set_usec (const long int&) throw ();
    /*! @brief  set the millisecond ;*/
    void set_msec (const long int&) throw ();
    /*! @brief  set the second ;*/
    void set_sec (const long int&) throw ();

    /*! @brief  update the time ;*/
    void update () throw ();

    /*! @brief  elapse microseconds ;*/
    long int elapsed_usec () const throw ();
    /*! @brief  elapse milliseconds ;*/
    long int elapsed_msec () const throw ();
    /*! @brief  elapse second ;*/
    long int elapsed_sec () const throw ();

    /*! @brief  add the microseconds ;*/
    void add_usec (long int) throw ();
    /*! @brief  add the milliseconds ;*/
    void add_msec (long int) throw ();
    /*! @brief  add the second ;*/
    void add_sec (long int) throw ();

    /*! @brief  the difference between the different time;*/
    long int diff_usec (const Time&) const throw ();
    long int diff_msec (const Time&) const throw ();
    long int diff_sec (const Time&) const throw ();


    bool operator== (const Time&) const throw ();
    bool operator!= (const Time&) const throw ();
    bool operator<= (const Time&) const throw ();
    bool operator< (const Time&) const throw ();
    bool operator>= (const Time&) const throw ();
    bool operator> (const Time&) const throw ();

    /*! @brief  set the time ;*/
    void set (const timeval&) throw ();
    /*! @brief  get the time ;*/
    void get (timeval&) const throw ();


public:
  long int sec;
  long int usec;

  static const Time starting_time;
  };

}

// const nubot::Time nubot::Time::starting_time;


inline nubot::Time::Time () throw ()
{
  update ();
}
inline nubot::Time::Time (const nubot::Time& src) throw () : sec (src.sec), usec (src.usec) {;}
inline nubot::Time::Time (const timeval& tv) throw () {
  set (tv);
}
inline const nubot::Time& nubot::Time::operator= (const nubot::Time& src) throw () {
  sec=src.sec;
  usec=src.usec;
  return *this;
}

/*//!set the global time
void
nubot::Time::set_usec (const long int& d) throw () {
  sec=starting_time.sec;
  usec=starting_time.usec;
  add_usec (d);
}

void
nubot::Time::set_msec (const long int& d) throw () {
  sec=starting_time.sec;
  usec=starting_time.usec;
  add_msec (d);
}

void
nubot::Time::set_sec (const long int& d) throw () {
  sec=starting_time.sec;
  usec=starting_time.usec;
  add_sec (d);
}
*/
inline void
nubot::Time::update () throw () {
  timeval systime;
  struct timezone no_good;
  gettimeofday (&systime, &no_good);
  sec=systime.tv_sec;
  usec=systime.tv_usec;
}

inline long int nubot::Time::elapsed_usec () const throw () {
  Time now;
  return now.diff_usec (*this);
}

inline long int nubot::Time::elapsed_msec () const throw () {
  Time now;
  return now.diff_msec (*this);
}

inline long int nubot::Time::elapsed_sec () const throw () {
  Time now;
  return now.diff_sec (*this);
}

inline void
nubot::Time::add_usec (long int n) throw () {
  usec+=n;
  if (usec<0) {
    long int k=-usec/1000000+1;
    sec-=k;
    usec+=1000000*k;
  } else if (usec>=1000000) {
    long int k=usec/1000000;
    sec+=k;
    usec-=1000000*k;
  }
}

inline void
nubot::Time::add_msec (long int n) throw () {
  add_usec (1000*n);
}

inline void
nubot::Time::add_sec (long int n) throw () {
  sec+=n;
}

inline long int
nubot::Time::diff_usec (const nubot::Time& src) const throw () {
  return 1000000*(sec-src.sec)+(usec-src.usec);
}

inline long int
nubot::Time::diff_msec (const nubot::Time& src) const throw () {
  return 1000*(sec-src.sec)+(usec-src.usec)/1000;
}

inline long int
nubot::Time::diff_sec (const nubot::Time& src) const throw () {
  return sec-src.sec;
}

inline bool
nubot::Time::operator== (const nubot::Time& src) const throw () {
  return ((sec==src.sec) && (usec==src.usec));
}

inline bool
nubot::Time::operator!= (const nubot::Time& src) const throw () {
  return !operator==(src);
}

inline bool
nubot::Time::operator<= (const nubot::Time& src) const throw () {
  return (diff_usec (src)<=0);
}

inline bool
nubot::Time::operator< (const nubot::Time& src) const throw () {
  return (diff_usec (src)<0);
}

inline bool
nubot::Time::operator>= (const nubot::Time& src) const throw () {
  return (diff_usec (src)>=0);
}

inline bool
nubot::Time::operator> (const nubot::Time& src) const throw () {
  return (diff_usec (src)>0);
}

/*//!get the global time
long int
nubot::Time::get_usec () const throw () {
  return (sec-Time::starting_time.sec)*1000000+usec-Time::starting_time.usec;
}

long int
nubot::Time::get_msec () const throw () {
  return (sec-Time::starting_time.sec)*1000+(usec-Time::starting_time.usec)/1000;
}

long int
nubot::Time::get_sec () const throw () {
  return (sec-Time::starting_time.sec);
}
*/
inline void
nubot::Time::set (const timeval& tv) throw () {
  sec=tv.tv_sec;
  usec=tv.tv_usec;
}

inline void
nubot::Time::get (timeval& tv) const throw () {
  tv.tv_sec=sec;
  tv.tv_usec=usec;
}


#endif //NUBOT_TIME_HPP_

