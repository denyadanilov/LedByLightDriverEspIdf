#include "gisteresys_model.hpp"

#define UPPER_THRESHOLD 3000
#define LOWER_THRESHOLD 1000

namespace ledbylight {

uint32_t gisteresys_model::get_limited_value(uint32_t analog_value) {
  if (analog_value > UPPER_THRESHOLD) {
    is_over_threshold = true;
  } else if (analog_value < LOWER_THRESHOLD && is_over_threshold) {
    is_over_threshold = false;
  }

  return is_over_threshold ? 0 : analog_value;
}

} // namespace ledbylight