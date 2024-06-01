#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/platform/window_handle.hpp"

namespace Fractal {

class Swapchain {
public:
  void SetupSwapchain(VkDevice device, VkPhysicalDevice physical_device, VkAllocationCallbacks* allocator, VkSurfaceKHR surface, WindowHandle window);

public:
  void CreateSwapchain();
  void DestroySwapchain();
  
private:
  // Non-owned objects
  VkDevice device;
  VkPhysicalDevice physical_device;
  VkAllocationCallbacks* allocator;
  VkSurfaceKHR surface;
  WindowHandle window;
  
  // Owned objects
  VkSwapchainKHR swapchain;
  std::vector<VkImage> images;
  VkFormat image_format;
  VkExtent2D extent;
  std::vector<VkImageView> image_views;
};

}
