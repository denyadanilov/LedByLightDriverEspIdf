#include "application.hpp"
#include "common/analog_pin.hpp"
#include "output/pin_stats_logger.hpp"

namespace ledbylight {

void application::initialize() { this->analogPin->initialize(); }

void application::update() {
  const auto stats = this->analogPin->get_signal_stats();
  this->pinStatsLogger->try_log(stats);
}

} // namespace ledbylight