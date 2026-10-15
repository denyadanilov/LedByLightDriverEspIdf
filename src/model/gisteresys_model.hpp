#pragma once
#include <cstdint>

#include "abstract_gisteresys_model.hpp"

namespace ledbylight {

class gisteresys_model : public abstract_gisteresys_model {
public:
  uint32_t get_limited_value(uint32_t analog_value) override;

private:
  bool is_over_threshold = false;
};

} // namespace ledbylight