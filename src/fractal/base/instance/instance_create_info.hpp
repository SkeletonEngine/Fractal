#pragma once

#include "fractal/base/common/logger.hpp"

namespace Fractal {

struct InstanceCreateInfo {
  LoggerCallback logger_callback = nullptr;
};

}
