#pragma once

#include "fractal/backend/vulkan/common/vulkan_forward_declarations.hpp"

namespace Fractal {

class VulkanSwapchainSupportDetails {
public:
  VulkanSwapchainSupportDetails(VkPhysicalDevice device, VkSurfaceKHR surface);
  ~VulkanSwapchainSupportDetails();

public:
  bool IsSuitable() const;
  VkSurfaceFormatKHR ChooseSwapchainSurfaceFormat() const;
  VkPresentModeKHR ChooseSwapchainPresentMode() const;

private:
    VkSurfaceCapabilitiesKHR capabilities;
    VkSurfaceFormatKHR* formats = nullptr;
    uint32_t format_count = 0;
    VkPresentModeKHR* present_modes = nullptr;
    uint32_t present_mode_count = 0;
};

}
