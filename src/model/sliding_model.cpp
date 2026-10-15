#include "sliding_model.hpp"

namespace ledbylight {

uint32_t sliding_model::get_mitigated_value(uint32_t analog_value) {
  sum -= window[index];
  window[index] = analog_value;
  sum += analog_value;
  index = (index + 1) % SLIDING_MODEL_WINDOW_SIZE;
  if (count < SLIDING_MODEL_WINDOW_SIZE) {
    ++count;
  }
  return sum / count;
}

} // namespace ledbylight