#include "common/analog_pin.hpp"
#include "controller/application.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/adc_types.h"
#include "output/pin_stats_logger.hpp"

#define LED_OUTPUT_PIN 18

#ifdef __cplusplus
extern "C" {
#endif

common::analog_pin analog_input(ADC_UNIT_1, ADC_CHANNEL_7);
output::pin_stats_logger pin_stats_logger;
ledbylight::application app(&analog_input, &pin_stats_logger);

void app_main() {
  app.initialize();
  while (1) {
    app.update();
    vTaskDelay(1);
  }
}
#ifdef __cplusplus
}
#endif