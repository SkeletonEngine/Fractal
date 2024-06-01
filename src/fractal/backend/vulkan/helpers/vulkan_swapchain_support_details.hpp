#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/platform/window_handle.hpp"

namespace Fractal {

class SwapchainSupportDetails {
public:
  SwapchainSupportDetails(VkPhysicalDevice device, VkSurfaceKHR surface, WindowHandle window);
  ~SwapchainSupportDetails();

public:
  bool IsSuitable() const;
  
private:
  VkSurfaceFormatKHR ChooseSwapchainSurfaceFormat() const;
  VkPresentModeKHR ChooseSwapchainPresentMode() const;
  VkExtent2D ChooseSwapExtent(WindowHandle window) const;

public:
  VkSurfaceCapabilitiesKHR capabilities;
  
  VkSurfaceFormatKHR* formats = nullptr;
  uint32_t format_count = 0;
  VkPresentModeKHR* present_modes = nullptr;
  uint32_t present_mode_count = 0;
  
  VkSurfaceFormatKHR surface_format;
  VkPresentModeKHR present_mode;
  VkExtent2D extent;
};

}
