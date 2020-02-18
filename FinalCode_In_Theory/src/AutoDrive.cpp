#include "AutoDrive.h"

AutoDrive::AutoDrive(double vel_p,
                     double vel_i,
                     double vel_d,
                     double pos_p,
                     double pos_i,
                     double pos_d) :
  leftpospid(0, pos_p, pos_i, pos_d, -12000, 12000, -12000, 12000),
  rightpospid(0, pos_p, pos_i, pos_d, -12000, 12000, -12000, 12000),
  leftvelpid(0, vel_p, vel_i, vel_d, -12000, 12000, -6000, 6000),
  rightvelpid(0, vel_p, vel_i, vel_d, -12000, 12000, -6000, 6000),
  l_power(0),
  r_power(0),
  start_ldist(0),
  start_rdist(0),
  last_ldist(0),
  last_rdist(0),
  base_lvel(0),
  base_rvel(0),
  next_base_lvel(0),
  next_base_rvel(0),
  initialized(false),
  is_running(false),
  is_done(false),
  transition(0),
  end_thresh(0),
  curr(),
  next(),
  time(),
  last_time(0)
{
}

void AutoDrive::initDrive(const AutoDriveConfig *config, 
                          const AutoDriveConfig *next_config, 
                          double transition_dist,
                          double thresh)
{
  if(std::abs(config->left_dist) > std::abs(config->right_dist))
  {
    base_lvel = sign(config->left_dist)*config->max_speed;
    base_rvel = sign(config->right_dist)*
                     config->max_speed*
                     std::abs(config->right_dist/config->left_dist);
  }
  else
  {
    base_rvel = sign(config->right_dist)*config->max_speed;
    base_lvel = sign(config->left_dist)*
                     config->max_speed*
                     (std::abs(config->right_dist) > 0.001 ? std::abs(config->left_dist/config->right_dist) : 0);
  }

  if(std::abs(next_config->left_dist) > std::abs(next_config->right_dist))
  {
    next_base_lvel = sign(next_config->left_dist)*next_config->max_speed;
    next_base_rvel = sign(next_config->right_dist)*
                     next_config->max_speed*
                     std::abs(next_config->right_dist/next_config->left_dist);
  }
  else
  {
    next_base_rvel = sign(next_config->right_dist)*next_config->max_speed;
    next_base_lvel = sign(next_config->left_dist)*
                     next_config->max_speed*
                     (std::abs(next_config->right_dist) > 0.001 ? std::abs(next_config->left_dist/next_config->right_dist) : 0);
  }

  initialized = true;
  is_running = false;
  is_done = false;
  curr = config;
  transition = transition_dist;
  next = next_config;
  end_thresh = thresh;
}

void AutoDrive::update(int32_t l_enc, int32_t r_enc)
{
  if(!is_running)
  {
    start_ldist = l_enc;
    start_rdist = r_enc;
    last_ldist = 0;
    last_rdist = 0;

    l_power = 0;
    r_power = 0;

    time.clear();
    last_time = time.time() / 1000.0;

    is_running = true;
  }
  else
  {
    int32_t curr_ldist = l_enc - start_ldist;
    int32_t curr_rdist = r_enc - start_rdist;

    double lvel_target = base_lvel;
    double rvel_target = base_rvel;

    if(std::min(std::abs(curr_ldist - curr->left_dist), std::abs(curr_rdist - curr->right_dist)) < std::abs(transition))
    {
      double lerp_prop = std::abs(1 - std::min(std::abs(curr_ldist - curr->left_dist), 
                                              std::abs(curr_rdist - curr->right_dist))/std::abs(transition));

      lvel_target += (next_base_lvel - base_lvel)*lerp_prop;
      rvel_target += (next_base_rvel - base_rvel)*lerp_prop;
    }

    if(std::abs(curr->left_dist) > std::abs(curr->right_dist))
    {
      rightpospid.setTarget(((double)curr->right_dist/(double)curr->left_dist)*curr_ldist);
      rvel_target += rightpospid.compute(curr_rdist);
    }
    else
    {
      leftpospid.setTarget(((double)curr->left_dist/(double)curr->right_dist)*curr_rdist);
      lvel_target += leftpospid.compute(curr_ldist);
    }

    double curr_time = time.time() / 1000.0;
    double dt = curr_time - last_time;
    last_time = curr_time;

    int32_t lvel = (curr_ldist - last_ldist) / dt;
    int32_t rvel = (curr_rdist - last_rdist) / dt;
    last_ldist = curr_ldist;
    last_rdist = curr_rdist;

    leftvelpid.setTarget(lvel_target);
    rightvelpid.setTarget(rvel_target);
    l_power = (int32_t)leftvelpid.compute(lvel);
    r_power = (int32_t)rightvelpid.compute(rvel);

    Brain.Screen.printAt(10, 20, "base lpos: %f", curr->left_dist);
    Brain.Screen.printAt(10, 40, "base rpos: %f", curr->right_dist);
    Brain.Screen.printAt(10, 60, "lpos: %d", curr_ldist);
    Brain.Screen.printAt(10, 80, "rpos: %d", curr_rdist);
    Brain.Screen.printAt(10, 100, "base lvel: %f", base_lvel);
    Brain.Screen.printAt(10, 120, "base rvel: %f", base_rvel);
    Brain.Screen.printAt(10, 140, "lvel: %f", lvel_target);
    Brain.Screen.printAt(10, 160, "rvel: %f", rvel_target);

    if(std::max(std::abs(curr_ldist - curr->left_dist), 
                std::abs(curr_rdist - curr->right_dist)) < std::abs(end_thresh))
    {
      leftpospid.stop();
      rightpospid.stop();
      leftpospid.stop();
      rightpospid.stop();
      is_done = true;
      initialized = false;
      is_running = false;
    }
  }
}

int32_t AutoDrive::leftPower()
{
  return l_power;
}

int32_t AutoDrive::rightPower()
{
  return r_power;
}

bool AutoDrive::complete()
{
  return is_done;
}