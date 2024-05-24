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

}
