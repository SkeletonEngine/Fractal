#include "vulkan_swapchain_support_details.hpp"

#include <algorithm>
#include <cstdint>
#include <limits>

#include <volk.h>

#include "fractal/base/platform/window_handle.hpp"

namespace Fractal {

VulkanSwapchainSupportDetails::VulkanSwapchainSupportDetails(VkPhysicalDevice device, VkSurfaceKHR surface, const WindowHandle& window) {
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities);

  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);
  if (format_count != 0) {
    formats = new VkSurfaceFormatKHR[format_count];
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, formats);
  }

  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);
  if (present_mode_count != 0) {
      present_modes = new VkPresentModeKHR[present_mode_count];
      vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, present_modes);
  }
  
  surface_format = ChooseSwapchainSurfaceFormat();
  present_mode = ChooseSwapchainPresentMode();
  extent = ChooseSwapExtent(window);
  
  glm::ivec2 size = GetWindowFramebufferExtent(window);
}

VulkanSwapchainSupportDetails::~VulkanSwapchainSupportDetails() {
  delete formats;
  delete present_modes;
}

bool VulkanSwapchainSupportDetails::IsSuitable() const {
  return format_count && present_mode_count;
}

VkSurfaceFormatKHR VulkanSwapchainSupportDetails::ChooseSwapchainSurfaceFormat() const {
  for (int i = 0; i < format_count; ++i) {
    VkSurfaceFormatKHR format = formats[i];
    if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return format;
    }
  }
  return formats[0];
}

VkPresentModeKHR VulkanSwapchainSupportDetails::ChooseSwapchainPresentMode() const {
  // TODO: Allow choosing this
  for (int i = 0; i < present_mode_count; ++i) {
    if (present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
      return VK_PRESENT_MODE_MAILBOX_KHR;
    }
  }
  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapchainSupportDetails::ChooseSwapExtent(const WindowHandle& window) const {
  if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    glm::ivec2 size = GetWindowFramebufferExtent(window);

    VkExtent2D actualExtent = { 
      static_cast<uint32_t>(size.x),
      static_cast<uint32_t>(size.y),
    };

    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
  }
}

}
