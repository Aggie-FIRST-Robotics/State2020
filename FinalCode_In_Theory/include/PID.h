#pragma once

#include "vex.h"

template <typename T>
class PID
{
public:
  PID(T initial_target,
      T pterm,
      T iterm,
      T dterm,
      T minimum,
      T maximum,
      T i_minimum,
      T i_maximum) :
    p_term(pterm),
    i_term(iterm),
    d_term(dterm),
    min(minimum),
    max(maximum),
    i_min(i_minimum),
    i_max(i_maximum),
    i_val(0),
    target(initial_target),
    last_sensed(0),
    initialized(false),
    time(),
    t_sample(0.0)
  {
  }

  T compute(T sensed_val)
  {
    T error = target - sensed_val;

    T p_val = p_term * error;
    T pid_val = p_val;
    double curr_time = time.time()/1000.0;

    if(initialized)
    {
      double dt = curr_time - t_sample;

      i_val += (T)(i_term * error * dt);
      if(i_val > i_max)
      {
        i_val = i_max;
      }
      else if(i_val < i_min)
      {
        i_val = i_min;
      }
      pid_val += i_val;

      T d_val = 0;
      d_val = (T) (d_term * (sensed_val - last_sensed) / dt);
      pid_val -= d_val;
    }
    else
    {
      initialized = true;
    }

    t_sample = curr_time;
    last_sensed = sensed_val;

    if(pid_val > max)
    {
      pid_val = max;
    }
    else if(pid_val < min)
    {
      pid_val = min;
    }
    return pid_val;
  }

  void setTarget(T _target)
  {
    target = _target;
  }

  void setBounds(T minimum, T maximum)
  {
    if(minimum < maximum)
    {
      min = minimum;
      max = maximum;
    }
  }

  void setIBounds(T i_minimum, T i_maximum)
  {
    if(i_minimum < i_maximum)
    {
      i_min = i_minimum;
      i_max = i_maximum;
    }
  }

  void stop()
  {
    initialized = false;
    time.clear();
  }

private:
  T p_term;
  T i_term;
  T d_term;
  T min;
  T max;
  T i_min;
  T i_max;
  T i_val;
  T target;
  T last_sensed;
  bool initialized;
  vex::timer time;
  double t_sample;
};