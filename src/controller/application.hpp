#pragma once
#include "common/analog_pin.hpp"
#include "output/pin_stats_logger.hpp"

namespace ledbylight {

class application {
public:
  application(common::analog_pin *analogPin,
              output::pin_stats_logger *pinStatsLogger)
      : analogPin(analogPin), pinStatsLogger(pinStatsLogger) {};
  void initialize();
  void update();

private:
  common::analog_pin *analogPin;
  output::pin_stats_logger *pinStatsLogger;

  application() = delete;
};

} // namespace ledbylight