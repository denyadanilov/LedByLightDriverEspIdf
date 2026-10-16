#include "pin_stats_logger.hpp"
#include "esp_log.h"
#include "esp_timer.h"

#define TAG "PinStatsLogger"
#define LOG_DELAY_MS 100

namespace output {

void pin_stats_logger::try_log(const common::signal_stats &stats) {
  const auto current_time = esp_timer_get_time();
  if (current_time - this->last_log_time < LOG_DELAY_MS * 1000) {
    return;
  }
  this->last_log_time = current_time;

  ESP_LOGI(TAG,
           "Raw Value: %d, Calibrated Value: %d, Raw Voltage: %d, Calibrated "
           "Voltage: %d, Bias Percentage: %d",
           stats.raw_value, stats.calibrated_value, stats.raw_voltage,
           stats.calibrated_voltage, stats.bias_percentage);
}

} // namespace output