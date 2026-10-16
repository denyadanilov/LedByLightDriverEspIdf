#pragma once

#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"

namespace common {

struct signal_stats {
  int raw_value;
  int calibrated_value;
  int raw_voltage;
  int calibrated_voltage;
  int bias_percentage;
};

class analog_pin {
public:
  analog_pin(adc_unit_t unit, adc_channel_t channel)
      : unit(unit), channel(channel) {}
  ~analog_pin();
  void initialize();
  signal_stats get_signal_stats();

private:
  adc_unit_t unit;
  adc_channel_t channel;
  adc_oneshot_unit_handle_t adc_handle = nullptr;
  adc_cali_handle_t adc_cali_chan_handle;
  bool do_calibration_chan;
  bool adc_calibration_init(adc_unit_t unit, adc_channel_t channel,
                            adc_atten_t atten, adc_cali_handle_t *out_handle);
};

} // namespace common