#include "CollisionDetectionZurlo.h"

#include <mc_control/GlobalPluginMacros.h>

namespace mc_plugin
{

CollisionDetectionZurlo::~CollisionDetectionZurlo() = default;

void CollisionDetectionZurlo::init(mc_control::MCGlobalController & controller, const mc_rtc::Configuration & config)
{
  mc_rtc::log::info("CollisionDetectionZurlo::init called with configuration:\n{}", config.dump(true, true));
}

void CollisionDetectionZurlo::reset(mc_control::MCGlobalController & controller)
{
  mc_rtc::log::info("CollisionDetectionZurlo::reset called");
}

void CollisionDetectionZurlo::before(mc_control::MCGlobalController &)
{
  mc_rtc::log::info("CollisionDetectionZurlo::before");
}

void CollisionDetectionZurlo::after(mc_control::MCGlobalController & controller)
{
  mc_rtc::log::info("CollisionDetectionZurlo::after");
}

mc_control::GlobalPlugin::GlobalPluginConfiguration CollisionDetectionZurlo::configuration()
{
  mc_control::GlobalPlugin::GlobalPluginConfiguration out;
  out.should_run_before = true;
  out.should_run_after = true;
  out.should_always_run = true;
  return out;
}

} // namespace mc_plugin

EXPORT_MC_RTC_PLUGIN("CollisionDetectionZurlo", mc_plugin::CollisionDetectionZurlo)
