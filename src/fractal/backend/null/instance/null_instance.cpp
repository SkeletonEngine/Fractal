#include "fractal/base/instance/instance.hpp"
#include "fractal/base/common/base.hpp"

#include "fractal/backend/null/instance/null_instance_data.hpp"

namespace Fractal {

bool FailingFunction(int x, int y) {
  return 0;
}

Instance::Instance(const InstanceCreateInfo& create_info) {
  instance = new InstanceData();
  FL_LOG_TRACE("Null Instance created");
}

Instance::~Instance() {
  FL_LOG_TRACE("Null Instance destroyed");
  delete instance;
}

}
