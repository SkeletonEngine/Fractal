#include "vulkan_swapchain_support_details.hpp"

#include <volk.h>

namespace Fractal {

VulkanSwapchainSupportDetails::VulkanSwapchainSupportDetails(VkPhysicalDevice device, VkSurfaceKHR surface) {
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

}
