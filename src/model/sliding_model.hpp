#pragma once

#include <cstddef>

#include "abstract_sliding_model.hpp"

namespace ledbylight {

#define SLIDING_MODEL_WINDOW_SIZE 8

class sliding_model : public abstract_sliding_model {
public:
  uint32_t get_mitigated_value(uint32_t analog_value) override;

private:
  uint32_t window[SLIDING_MODEL_WINDOW_SIZE] = {};
  size_t index = 0;
  size_t count = 0;
  uint32_t sum = 0;
};

} // namespace ledbylight