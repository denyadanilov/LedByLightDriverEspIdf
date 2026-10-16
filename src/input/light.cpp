#include "light.hpp"

namespace ledbylight {

void light::initialize() { pin->initialize(); }

uint32_t light::get_value() {
  auto result = pin->get_signal_stats().calibrated_value;
  return result;
}
} // namespace ledbylight