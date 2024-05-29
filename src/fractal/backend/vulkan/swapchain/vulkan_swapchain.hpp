#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/platform/window_handle.hpp"

namespace Fractal {

class Swapchain {
public:
  Swapchain(VkPhysicalDevice device, VkSurfaceKHR surface, const WindowHandle& window);
  
public:
  void CreateSwapchain();
  void DestroySwapchain();
  
private:
  VkPhysicalDevice device;
  VkSurfaceKHR surface;
  const WindowHandle& window;
};

}
