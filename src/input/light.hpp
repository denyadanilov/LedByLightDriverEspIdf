#pragma once

#include "abstract_light.hpp"
#include "common/analog_pin.hpp"

namespace ledbylight {

class light : public abstract_light {
public:
  light(common::analog_pin *pin) : pin(pin) {}
  void initialize() override;
  uint32_t get_value() override;

private:
  common::analog_pin *pin;
};

} // namespace ledbylight