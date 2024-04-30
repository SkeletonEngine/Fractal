#pragma once

#include <volk.h>

namespace Fractal {

struct InstanceData;

struct WindowSurfaceData {
  InstanceData* instance;
  
  VkSurfaceKHR surface;
};

}
