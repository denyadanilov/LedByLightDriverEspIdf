#pragma once
#include "input/abstract_light.hpp"
#include "model/abstract_gisteresys_model.hpp"
#include "model/abstract_sliding_model.hpp"
#include "output/abstract_led.hpp"

namespace ledbylight {

class application {
public:
  application(abstract_led *led, abstract_light *light,
              abstract_sliding_model *sliding_model,
              abstract_gisteresys_model *gisteresys_model);
  void initialize();
  void update();

private:
  abstract_led *led;
  abstract_light *light;
  abstract_sliding_model *sliding_model;
  abstract_gisteresys_model *gisteresys_model;

  // Disable the default constructor
  application() = delete;
};

} // namespace ledbylight