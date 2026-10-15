#include "controller/application.hpp"
#include "hal/adc_types.h"
#include "input/light.hpp"
#include "model/sliding_model.hpp"
#include "output/led.hpp"

#define LED_OUTPUT_PIN 18

#ifdef __cplusplus
extern "C" {
#endif

ledbylight::led output(LED_OUTPUT_PIN);
ledbylight::light input(ADC_UNIT_1, ADC_CHANNEL_7);
ledbylight::sliding_model model;
ledbylight::application app(&output, &input, &model);

void app_main() {
  app.initialize();
  while (1) {
    app.update();
  }
}
#ifdef __cplusplus
}
#endif