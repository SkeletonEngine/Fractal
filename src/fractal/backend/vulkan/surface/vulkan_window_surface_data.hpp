#pragma once

#include <volk.h>

namespace Fractal {

struct InstanceData;

struct WindowSurfaceData {
  InstanceData* instance = nullptr;
  
  VkSurfaceKHR surface = VK_NULL_HANDLE;
};

}
