#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

namespace Fractal {

struct InstanceData;
class Swapchain;

struct WindowSurfaceData {
  InstanceData* instance = nullptr;
  
  VkSurfaceKHR surface = VK_NULL_HANDLE;

  Swapchain* swapchain = nullptr;
};

}
