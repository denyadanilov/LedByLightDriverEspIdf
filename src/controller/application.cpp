#include "application.hpp"

namespace ledbylight {

application::application(abstract_led *led, abstract_light *light,
                         abstract_sliding_model *sliding_model) {
  this->led = led;
  this->light = light;
  this->sliding_model = sliding_model;
}

void application::initialize() {
  this->led->initialize();
  this->light->initialize();
}

void application::update() {
  auto light_value = this->light->get_value();
  auto mitigated_value = this->sliding_model->get_mitigated_value(light_value);
  this->led->update(mitigated_value);
}

} // namespace ledbylight