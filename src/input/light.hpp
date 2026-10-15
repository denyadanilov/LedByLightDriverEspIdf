#pragma once

#include "abstract_light.hpp"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"

namespace ledbylight {

class light : public abstract_light {
public:
  explicit light(adc_unit_t unit, adc_channel_t channel);
  void initialize() override;
  uint32_t get_value() override;
  ~light() override;

private:
  adc_unit_t adc_unit;
  adc_channel_t adc_channel;
  adc_oneshot_unit_handle_t adc_handle = nullptr;
  adc_cali_handle_t adc_cali_chan_handle;
  bool do_calibration_chan;
  bool adc_calibration_init(adc_unit_t unit, adc_channel_t channel,
                            adc_atten_t atten, adc_cali_handle_t *out_handle);
};

} // namespace ledbylight