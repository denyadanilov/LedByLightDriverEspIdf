#include "led.hpp"

#include "driver/ledc.h"
#include "esp_err.h"

namespace ledbylight {

constexpr uint32_t OUTPUT_PWM_FREQUENCY_HZ = 5000;
constexpr uint32_t MAX_ANALOG_VALUE = 4095;
constexpr uint32_t MAX_PWM_DUTY = (1 << LEDC_TIMER_13_BIT) - 1;

led::led(uint8_t output_pin) : output_pin(output_pin) {}

void led::initialize() {
  if (!this->initialized) {
    ledc_timer_config_t timer = {};
    timer.speed_mode = LEDC_LOW_SPEED_MODE;
    timer.duty_resolution = LEDC_TIMER_13_BIT;
    timer.timer_num = LEDC_TIMER_0;
    timer.freq_hz = OUTPUT_PWM_FREQUENCY_HZ;
    timer.clk_cfg = LEDC_AUTO_CLK;
    ESP_ERROR_CHECK(ledc_timer_config(&timer));

    ledc_channel_config_t channel = {};
    channel.gpio_num = this->output_pin;
    channel.speed_mode = LEDC_LOW_SPEED_MODE;
    channel.channel = LEDC_CHANNEL_0;
    channel.timer_sel = LEDC_TIMER_0;
    channel.duty = 0;
    channel.hpoint = 0;
    ESP_ERROR_CHECK(ledc_channel_config(&channel));
    this->initialized = true;
  }
}

void led::update(uint32_t analog_value) {

  if (!this->initialized) {
    this->initialize();
  }

  if (analog_value > MAX_ANALOG_VALUE) {
    analog_value = MAX_ANALOG_VALUE;
  }

  const uint32_t duty = analog_value * MAX_PWM_DUTY / MAX_ANALOG_VALUE;
  ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
}

} // namespace ledbylight
