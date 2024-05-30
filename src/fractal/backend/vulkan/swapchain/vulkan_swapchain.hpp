#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/platform/window_handle.hpp"

namespace Fractal {

class Swapchain {
public:
  Swapchain(VkDevice device, VkPhysicalDevice physical_device, VkAllocationCallbacks* allocator, VkSurfaceKHR surface, const WindowHandle& window);
  
public:
  void CreateSwapchain();
  void DestroySwapchain();
  
private:
  // Non-owned objects
  VkDevice device;
  VkPhysicalDevice physical_device;
  VkAllocationCallbacks* allocator;
  VkSurfaceKHR surface;
  const WindowHandle& window;
  
  // Owned objects
  VkSwapchainKHR swapchain;
};

}
