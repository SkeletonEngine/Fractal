#include "vulkan_queue_family_indices.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

namespace Fractal {

VulkanQueueFamilyIndices::VulkanQueueFamilyIndices(VkPhysicalDevice physical_device, VkSurfaceKHR surface) {
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

  for (int i = 0; i < queue_family_count; ++i) {
    if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      graphics_family = i;
    }

    // Note: the availability of a presentation queue implies that VK_KHR_swapchain must be supported
    VkBool32 present_support = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &present_support);
    if (present_support) {
      present_family = i;
    }

    // Prefer a single queue that can do both graphics and present, as this often results in better performance
    if (graphics_family == present_family) {
      break;
    }
  }
}

int VulkanQueueFamilyIndices::GetGraphicsFamily() const {
  return graphics_family;
}

int VulkanQueueFamilyIndices::GetPresentFamily() const {
  return present_family;
}

bool VulkanQueueFamilyIndices::IsComplete() const {
  return graphics_family != -1 && present_family != -1;
}

}
