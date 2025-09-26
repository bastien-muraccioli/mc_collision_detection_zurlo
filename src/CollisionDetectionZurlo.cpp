#include "CollisionDetectionZurlo.h"

#include <mc_control/GlobalPluginMacros.h>

namespace mc_plugin
{

CollisionDetectionZurlo::~CollisionDetectionZurlo() = default;

void CollisionDetectionZurlo::init(mc_control::MCGlobalController & controller, const mc_rtc::Configuration & config)
{
  auto & ctl = static_cast<mc_control::MCGlobalController &>(controller);
  if(!ctl.controller().datastore().has("Zurlo Collision Detection"))
  {
    ctl.controller().datastore().make<bool>("Zurlo Collision Detection", false);
  }
  // Make sure to have obstacle detection
  if(!ctl.controller().datastore().has("Obstacle detected"))
  {
    ctl.controller().datastore().make<bool>("Obstacle detected", false);
  }

  addGui(ctl);
  addLog(ctl);
  mc_rtc::log::info("CollisionDetectionZurlo::init called with configuration:\n{}", config.dump(true, true));
}

void CollisionDetectionZurlo::reset(mc_control::MCGlobalController & controller)
{
  mc_rtc::log::info("CollisionDetectionZurlo::reset called");
}

void CollisionDetectionZurlo::before(mc_control::MCGlobalController & controller)
{
  auto & ctl = static_cast<mc_control::MCGlobalController &>(controller);
  // mc_rtc::log::info("CollisionDetectionZurlo::before");
  obstacle_detected_ = false;
  obstacle_detected_with_torque_residual_ = false;
  obstacle_detected_with_current_residual_ = false;
  ctl.controller().datastore().get<bool>("Zurlo Collision Detection") = collision_stop_activated_;

  
  if(ctl.controller().datastore().has("Energy Residual Obstacle detected"))
  {
    energy_residual_obstacle_detected_ = ctl.controller().datastore().get<bool>("Energy Residual Obstacle detected");
  }
  else
  {
    mc_rtc::log::error("[CollisionDetectionZurlo] Energy Residual Obstacle detected not found in datastore");
  }
  if(ctl.controller().datastore().has("Current Residual Obstacle detected"))
  {
    current_residual_obstacle_detected_ = ctl.controller().datastore().get<bool>("Current Residual Obstacle detected");
  }
  else
  {
    if(use_current_residual_) mc_rtc::log::error("[CollisionDetectionZurlo] Current Residual Obstacle detected not found in datastore");
  }
  if(ctl.controller().datastore().has("Torque Residual Obstacle detected"))
  {
    torque_residual_obstacle_detected_ = ctl.controller().datastore().get<bool>("Torque Residual Obstacle detected");
  }
  else
  {
    if(use_torque_residual_) mc_rtc::log::error("[CollisionDetectionZurlo] Torque Residual Obstacle detected not found in datastore");
  }

  if(energy_residual_obstacle_detected_ && current_residual_obstacle_detected_)
  {
    if(activate_verbose) mc_rtc::log::info("[CollisionDetectionZurlo] Obstacle detected with current residual");
    obstacle_detected_with_current_residual_ = true;
    if(use_current_residual_)
    {
      obstacle_detected_ = true;
    
      if(collision_stop_activated_)
      {
        ctl.controller().datastore().get<bool>("Obstacle detected") = obstacle_detected_;
      }
    } 
  }
  if(energy_residual_obstacle_detected_ && torque_residual_obstacle_detected_)
  {
    if(activate_verbose) mc_rtc::log::info("[CollisionDetectionZurlo] Obstacle detected with torque residual");
    obstacle_detected_with_torque_residual_ = true;
    if(use_torque_residual_)
    {
      obstacle_detected_ = true;
      if(collision_stop_activated_)
      {
        ctl.controller().datastore().get<bool>("Obstacle detected") = obstacle_detected_;
      }

    }
  }
}

void CollisionDetectionZurlo::after(mc_control::MCGlobalController & controller)
{
  // mc_rtc::log::info("CollisionDetectionZurlo::after");
}

mc_control::GlobalPlugin::GlobalPluginConfiguration CollisionDetectionZurlo::configuration()
{
  mc_control::GlobalPlugin::GlobalPluginConfiguration out;
  out.should_run_before = true;
  out.should_run_after = false;
  out.should_always_run = true;
  return out;
}

void CollisionDetectionZurlo::addGui(mc_control::MCGlobalController & controller)
{
  auto & ctl = static_cast<mc_control::MCGlobalController &>(controller);
  ctl.controller().gui()->addElement({"Plugins", "CollisionDetectionZurlo"},
    mc_rtc::gui::Checkbox("Collision stop", collision_stop_activated_),
    mc_rtc::gui::Checkbox("Use torque residual", use_torque_residual_),
    mc_rtc::gui::Checkbox("Use current residual", use_current_residual_),
    mc_rtc::gui::Checkbox("Verbose", activate_verbose)
    );
  
}

void CollisionDetectionZurlo::addLog(mc_control::MCGlobalController & controller)
{
  auto & ctl = static_cast<mc_control::MCGlobalController &>(controller);
  ctl.controller().logger().addLogEntry("CollisionDetectionZurlo_obstacleDetected_energyResidual", [this]() { return energy_residual_obstacle_detected_; });
  ctl.controller().logger().addLogEntry("CollisionDetectionZurlo_obstacleDetected_currentResidual", [this]() { return current_residual_obstacle_detected_; });
  ctl.controller().logger().addLogEntry("CollisionDetectionZurlo_obstacleDetected_torqueResidual", [this]() { return torque_residual_obstacle_detected_; });
  ctl.controller().logger().addLogEntry("CollisionDetectionZurlo_obstacleDetected", [this]() { return obstacle_detected_; });
  ctl.controller().logger().addLogEntry("CollisionDetectionZurlo_obstacleDetected_withTorqueResidual", [this]() { return obstacle_detected_with_torque_residual_; });
  ctl.controller().logger().addLogEntry("CollisionDetectionZurlo_obstacleDetected_withCurrentResidual", [this]() { return obstacle_detected_with_current_residual_; });
}

} // namespace mc_plugin

EXPORT_MC_RTC_PLUGIN("CollisionDetectionZurlo", mc_plugin::CollisionDetectionZurlo)
