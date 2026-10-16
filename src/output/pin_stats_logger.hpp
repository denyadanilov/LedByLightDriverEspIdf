#pragma once

#include "common/analog_pin.hpp"

namespace output {

class pin_stats_logger {
public:
  void try_log(const common::signal_stats &stats);

private:
  unsigned long last_log_time;
};

} // namespace output