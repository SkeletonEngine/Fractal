#pragma once
#include "fractal/backend/vulkan/common/vulkan_forward_declarations.hpp"

namespace Fractal {

struct InstanceData;

struct WindowSurfaceData {
  InstanceData* instance = nullptr;
  
  VkSurfaceKHR surface = VK_NULL_HANDLE;
};

}
