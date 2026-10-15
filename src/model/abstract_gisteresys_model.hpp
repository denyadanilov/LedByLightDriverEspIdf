#pragma once
#include <cstdint>

namespace ledbylight {

class abstract_gisteresys_model {
public:
  virtual uint32_t get_limited_value(uint32_t analog_value) = 0;
  virtual ~abstract_gisteresys_model() = default;
};

} // namespace ledbylight