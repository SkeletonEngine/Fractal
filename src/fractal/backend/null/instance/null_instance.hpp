#pragma once
#include "fractal/base/common/base.hpp"

#include "fractal/base/instance/instance_create_info.hpp"

namespace Fractal {

class Instance {
public:
  Instance(const InstanceCreateInfo& create_info = { });
  ~Instance();
};

}
