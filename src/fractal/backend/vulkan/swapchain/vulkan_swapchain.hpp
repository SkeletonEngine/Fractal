#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/platform/window_handle.hpp"

namespace Fractal {

class Swapchain {
public:
  void SetupSwapchain(VkDevice device, VkPhysicalDevice physical_device, VkAllocationCallbacks* allocator, VkSurfaceKHR surface, WindowHandle window);

  void CreateSwapchain();
  void DestroySwapchain();

private:
  void CreateImageViews();
  
private:
  // Non-owned objects
  VkDevice device;
  VkPhysicalDevice physical_device;
  VkAllocationCallbacks* allocator;
  VkSurfaceKHR surface;
  WindowHandle window;
  
  // Owned objects
  VkSwapchainKHR swapchain;
  VkImage* images;
  uint32_t image_count;
  VkFormat image_format;
  VkExtent2D extent;
};

}
