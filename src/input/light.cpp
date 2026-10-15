#include "light.hpp"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"
#include "esp_log.h"
#include "hal/adc_types.h"

namespace ledbylight {

#define TAG "LIGHT"
#define MAX_ADC_VALUE 4095
#define MAX_PIN_VOLTAGE 3300

light::light(adc_unit_t unit, adc_channel_t channel)
    : adc_unit(unit), adc_channel(channel) {}

void light::initialize() {
  adc_oneshot_unit_init_cfg_t init_config = {
      .unit_id = adc_unit,
      .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
      .ulp_mode = ADC_ULP_MODE_DISABLE,
  };
  ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

  adc_oneshot_chan_cfg_t config = {.atten = ADC_ATTEN_DB_12,
                                   .bitwidth = ADC_BITWIDTH_DEFAULT};
  ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, adc_channel, &config));

  do_calibration_chan =
      adc_calibration_init(this->adc_unit, this->adc_channel, ADC_ATTEN_DB_12,
                           &adc_cali_chan_handle);
}

light::~light() {
  if (adc_handle != nullptr) {
    ESP_ERROR_CHECK(adc_oneshot_del_unit(adc_handle));
  }
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
  if (do_calibration_chan) {
    ESP_ERROR_CHECK(adc_cali_delete_scheme_curve_fitting(adc_cali_chan_handle));
  }
#endif
}

uint32_t light::get_value() {
  auto raw_result = 0;
  auto result = 0;

  ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, adc_channel, &raw_result));

  if (do_calibration_chan) {
    auto calibrated_voltage = 0;

    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc_cali_chan_handle, raw_result,
                                            &calibrated_voltage));
    result = (calibrated_voltage * MAX_ADC_VALUE / MAX_PIN_VOLTAGE);
  } else {
    result = raw_result;
  }

  return result;
}

bool light::adc_calibration_init(adc_unit_t unit, adc_channel_t channel,
                                 adc_atten_t atten,
                                 adc_cali_handle_t *out_handle) {
  adc_cali_handle_t handle = NULL;
  esp_err_t ret = ESP_FAIL;
  bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
  if (!calibrated) {
    ESP_LOGI(TAG, "calibration scheme version is Curve Fitting");
    adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = unit,
        .chan = channel,
        .atten = atten,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
    if (ret == ESP_OK) {
      calibrated = true;
    }
  }
#endif

  *out_handle = handle;
  return calibrated;
}

} // namespace ledbylight