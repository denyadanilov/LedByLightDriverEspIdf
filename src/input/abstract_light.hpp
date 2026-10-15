#pragma once

#include <cstdint>

namespace ledbylight {

class abstract_light {
public:
  virtual void initialize() = 0;
  virtual uint32_t get_value() = 0;
  virtual ~abstract_light() = default;
};

} // namespace ledbylight