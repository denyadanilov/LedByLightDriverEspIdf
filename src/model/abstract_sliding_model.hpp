#pragma once

#include <cstdint>

namespace ledbylight {

class abstract_sliding_model {
public:
  virtual uint32_t get_mitigated_value(uint32_t analog_value) = 0;
  virtual ~abstract_sliding_model() = default;
};

} // namespace ledbylight