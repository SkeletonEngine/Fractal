#include "fractal/backend/null/instance/null_instance.hpp"
#include "fractal/base/common/base.hpp"

namespace Fractal {

Instance::Instance(const InstanceCreateInfo& create_info) {
  FL_LOG_TRACE("Null Instance created");
}

Instance::~Instance() {
  FL_LOG_TRACE("Null Instance destroyed");
}

}
