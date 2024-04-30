#pragma once
#include "fractal/base/common/base.hpp"

namespace Fractal {

struct InstanceCreateInfo {
};

struct InstanceData;

class Instance {
public:
  Instance(const InstanceCreateInfo& create_info = { });
  ~Instance();
  
private:
  InstanceData* data;
  
private:
  friend class WindowSurface;
};

}
