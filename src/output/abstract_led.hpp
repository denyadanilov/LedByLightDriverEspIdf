#pragma once

#include <cstdint>

namespace ledbylight {

class abstract_led {
public:
  virtual void initialize() = 0;
  virtual void update(uint32_t value) = 0;
  virtual ~abstract_led() = default;
};

} // namespace ledbylight