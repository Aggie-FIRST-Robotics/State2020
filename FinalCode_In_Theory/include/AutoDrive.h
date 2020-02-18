#pragma once

#include "PID.h"
#include "vex.h"
#include <cmath>

struct AutoDriveConfig
{
  double left_dist;
  double right_dist;
  double max_speed;

  AutoDriveConfig() :
    left_dist(0),
    right_dist(0),
    max_speed(0)
  {
  }

  AutoDriveConfig(double l_dist, double r_dist, double max_spd) :
    left_dist(l_dist),
    right_dist(r_dist),
    max_speed(max_spd)
  {
  }

  AutoDriveConfig(const AutoDriveConfig &copy) :
    left_dist(copy.left_dist),
    right_dist(copy.right_dist),
    max_speed(copy.max_speed)
  {
  }
};

class AutoDrive
{
public:
  AutoDrive(double vel_p,
            double vel_i,
            double vel_d,
            double pos_p,
            double pos_i,
            double pos_d);

  void initDrive(const AutoDriveConfig *config, 
                 const AutoDriveConfig *next_config, 
                 double transition_dist,
                 double thresh);

  void update(int32_t l_enc, int32_t r_enc);

  int32_t leftPower();

  int32_t rightPower();

  bool complete();

private:
  PID<double> leftpospid;
  PID<double> rightpospid;
  PID<double> leftvelpid;
  PID<double> rightvelpid;
  int32_t l_power;
  int32_t r_power;
  int32_t start_ldist;
  int32_t start_rdist;
  int32_t last_ldist;
  int32_t last_rdist;
  double base_lvel;
  double base_rvel;
  double next_base_lvel;
  double next_base_rvel;
  bool initialized;
  bool is_running;
  bool is_done;
  double transition;
  double end_thresh;
  const AutoDriveConfig *curr;
  const AutoDriveConfig *next;
  vex::timer time;
  double last_time;

  template<typename T>
  inline T sign(T x)
  {
    if(x > 0)
    {
      return 1;
    }
    else if(x < 0)
    {
      return -1;
    }
    return 0;
  }
};