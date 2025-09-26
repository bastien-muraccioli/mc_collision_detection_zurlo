/*
 * Copyright 2021 CNRS-UM LIRMM, CNRS-AIST JRL
 */

#pragma once

#include <mc_control/GlobalPlugin.h>

namespace mc_plugin
{

struct CollisionDetectionZurlo : public mc_control::GlobalPlugin
{
  void init(mc_control::MCGlobalController & controller, const mc_rtc::Configuration & config) override;

  void reset(mc_control::MCGlobalController & controller) override;

  void before(mc_control::MCGlobalController & controller) override;

  void after(mc_control::MCGlobalController & controller) override;

  void addGui(mc_control::MCGlobalController & controller);
  void addLog(mc_control::MCGlobalController & controller);

  mc_control::GlobalPlugin::GlobalPluginConfiguration configuration() override;

  ~CollisionDetectionZurlo() override;

private:
  bool collision_stop_activated_ = false;
  bool energy_residual_obstacle_detected_ = false;
  bool current_residual_obstacle_detected_ = false;
  bool torque_residual_obstacle_detected_ = false;
  bool obstacle_detected_ = false;
  bool obstacle_detected_with_torque_residual_ = false;
  bool obstacle_detected_with_current_residual_ = false;
  bool use_torque_residual_ = false;
  bool use_current_residual_ = true;
  bool activate_verbose = true;
};

} // namespace mc_plugin
