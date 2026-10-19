#include "model/gisteresys_model.cpp"
#include "model/gisteresys_model.hpp"
#include <unity.h>

void input_value_over_upper_threshold_returns_zero(void) {
  ledbylight::gisteresys_model model;
  auto limited_value = model.get_limited_value(UPPER_THRESHOLD + 1);
  TEST_ASSERT_EQUAL(limited_value, 0);
}

void input_value_equals_upper_threshold_returns_input_value(void) {
  ledbylight::gisteresys_model model;
  auto limited_value = model.get_limited_value(UPPER_THRESHOLD);
  TEST_ASSERT_EQUAL(limited_value, UPPER_THRESHOLD);
}

void input_value_under_upper_threshold_returns_input_value(void) {
  ledbylight::gisteresys_model model;
  auto limited_value = model.get_limited_value(UPPER_THRESHOLD - 1);
  TEST_ASSERT_EQUAL(limited_value, UPPER_THRESHOLD - 1);
}

void input_value_under_lower_threshold_returns_input_value(void) {
  ledbylight::gisteresys_model model;
  auto limited_value = model.get_limited_value(LOWER_THRESHOLD - 1);
  TEST_ASSERT_EQUAL(limited_value, LOWER_THRESHOLD - 1);
}

void input_value_over_than_lower_upper_threshold_returns_zero(void) {
  ledbylight::gisteresys_model model;
  auto limited_value_upper = model.get_limited_value(UPPER_THRESHOLD + 1);
  auto limited_value_lower = model.get_limited_value(UPPER_THRESHOLD - 1);
  TEST_ASSERT_EQUAL(limited_value_upper, 0);
  TEST_ASSERT_EQUAL(limited_value_lower, 0);
}

void input_value_over_upper_than_lower_lower_threshold_returns_zero(void) {
  ledbylight::gisteresys_model model;
  auto limited_value_upper = model.get_limited_value(UPPER_THRESHOLD + 1);
  auto limited_value_lower = model.get_limited_value(LOWER_THRESHOLD - 1);
  TEST_ASSERT_EQUAL(limited_value_upper, 0);
  TEST_ASSERT_EQUAL(limited_value_lower, LOWER_THRESHOLD - 1);
}

void input_value_over_upper_than_equals_lower_threshold_returns_zero(void) {
  ledbylight::gisteresys_model model;
  auto limited_value_upper = model.get_limited_value(UPPER_THRESHOLD + 1);
  auto limited_value_lower = model.get_limited_value(LOWER_THRESHOLD);
  TEST_ASSERT_EQUAL(limited_value_upper, 0);
  TEST_ASSERT_EQUAL(limited_value_lower, 0);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(input_value_over_upper_threshold_returns_zero);
  RUN_TEST(input_value_equals_upper_threshold_returns_input_value);
  RUN_TEST(input_value_under_upper_threshold_returns_input_value);
  RUN_TEST(input_value_under_lower_threshold_returns_input_value);
  RUN_TEST(input_value_over_than_lower_upper_threshold_returns_zero);
  RUN_TEST(input_value_over_upper_than_lower_lower_threshold_returns_zero);
  RUN_TEST(input_value_over_upper_than_equals_lower_threshold_returns_zero);
  return UNITY_END();
}