#pragma once

#include "abstract_led.hpp"
#include <cstdint>

namespace ledbylight {

class led : public abstract_led {
public:
  explicit led(uint8_t output_pin);
  void initialize() override;
  void update(uint32_t analog_value) override;

private:
  uint8_t output_pin;
  bool initialized = false;
};

} // namespace ledbylight
