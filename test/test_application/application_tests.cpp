#include "controller/application.cpp"
#include "controller/application.hpp"
#include "input/abstract_light.hpp"
#include "model/abstract_gisteresys_model.hpp"
#include "model/abstract_sliding_model.hpp"
#include "output/abstract_led.hpp"
#include <fakeit.hpp>
#include <unity.h>

using namespace fakeit;

void application_initialized_input_initialized(void) {
  Mock<ledbylight::abstract_light> mock_input;
  Fake(Method(mock_input, initialize));
  Mock<ledbylight::abstract_led> mock_output;
  Fake(Method(mock_output, initialize));
  Mock<ledbylight::abstract_gisteresys_model> mock_gisteresys_model;
  Mock<ledbylight::abstract_sliding_model> mock_sliding_model;

  ledbylight::application app(&mock_output.get(), &mock_input.get(),
                              &mock_sliding_model.get(),
                              &mock_gisteresys_model.get());

  app.initialize();

  Verify(Method(mock_input, initialize)).Once();
  Verify(Method(mock_output, initialize)).Once();
}

void application_updated_output_updated(void) {
  const uint32_t light_value = 42;
  const uint32_t mitigated_value = 47;
  Mock<ledbylight::abstract_light> mock_input;
  Fake(Method(mock_input, initialize));
  When(Method(mock_input, get_value)).Return(light_value);
  Mock<ledbylight::abstract_led> mock_output;
  Fake(Method(mock_output, initialize));
  Fake(Method(mock_output, update));
  Mock<ledbylight::abstract_gisteresys_model> mock_gisteresys_model;
  When(Method(mock_gisteresys_model, get_limited_value))
      .Return(mitigated_value);
  Mock<ledbylight::abstract_sliding_model> mock_sliding_model;
  When(Method(mock_sliding_model, get_mitigated_value).Using(light_value))
      .Return(mitigated_value);

  ledbylight::application app(&mock_output.get(), &mock_input.get(),
                              &mock_sliding_model.get(),
                              &mock_gisteresys_model.get());

  app.update();

  Verify(Method(mock_output, update)).Once();
  Verify(
      Method(mock_gisteresys_model, get_limited_value).Using(mitigated_value))
      .Once();
  Verify(Method(mock_sliding_model, get_mitigated_value).Using(light_value))
      .Once();
  Verify(Method(mock_output, update).Using(mitigated_value)).Once();

  Verify(Method(mock_sliding_model, get_mitigated_value) +
         Method(mock_gisteresys_model, get_limited_value) +
         Method(mock_output, update).Using(mitigated_value));
}

int main(void) {
  UNITY_BEGIN();
  // Add RUN_TEST calls here
  RUN_TEST(application_initialized_input_initialized);
  RUN_TEST(application_updated_output_updated);
  return UNITY_END();
}