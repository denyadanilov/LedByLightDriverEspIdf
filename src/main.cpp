#include "common/analog_pin.hpp"
#include "controller/application.hpp"
#include "hal/adc_types.h"
#include "input/light.hpp"
#include "model/gisteresys_model.hpp"
#include "model/sliding_model.hpp"
#include "output/led.hpp"

#define LED_OUTPUT_PIN 18

#ifdef __cplusplus
extern "C" {
#endif

common::analog_pin analog_input(ADC_UNIT_1, ADC_CHANNEL_7);
ledbylight::led output(LED_OUTPUT_PIN);
ledbylight::light input(&analog_input);
ledbylight::sliding_model sliding_model;
ledbylight::gisteresys_model gisteresys_model;
ledbylight::application app(&output, &input, &sliding_model, &gisteresys_model);

void app_main() {
  app.initialize();
  while (1) {
    app.update();
  }
}
#ifdef __cplusplus
}
#endif