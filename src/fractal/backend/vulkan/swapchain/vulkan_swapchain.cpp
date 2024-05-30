#include "vulkan_swapchain.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

#include "fractal/backend/vulkan/helpers/vulkan_swapchain_support_details.hpp"
#include "fractal/backend/vulkan/helpers/vulkan_queue_family_indices.hpp"

namespace Fractal {

Swapchain::Swapchain(VkDevice device, VkPhysicalDevice physical_device, VkAllocationCallbacks* allocator, VkSurfaceKHR surface, const WindowHandle& window)
  : device(device), physical_device(physical_device), allocator(allocator), surface(surface), window(window) {
    CreateSwapchain();
}

void Swapchain::CreateSwapchain() {
  VulkanSwapchainSupportDetails support(physical_device, surface, window);
  FL_LOG_TRACE("Createing swapchain with extent ({}, {})", support.extent.width, support.extent.height);
  
  uint32_t image_count = support.capabilities.minImageCount + 1;
  if (support.capabilities.maxImageCount > 0 && image_count > support.capabilities.maxImageCount) {
    image_count = support.capabilities.maxImageCount;
  }
  
  VkSwapchainCreateInfoKHR swapchain_info { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
  swapchain_info.surface = surface;
  swapchain_info.minImageCount = image_count;
  swapchain_info.imageFormat = support.surface_format.format;
  swapchain_info.imageColorSpace = support.surface_format.colorSpace;
  swapchain_info.imageExtent = support.extent;
  swapchain_info.imageArrayLayers = 1;
  swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  
  VulkanQueueFamilyIndices indices(physical_device, surface);
  uint32_t queue_family_indices[] = { indices.GetGraphicsFamily(), indices.GetPresentFamily() };

  if (indices.GetGraphicsFamily() != indices.GetPresentFamily()) {
    swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    swapchain_info.queueFamilyIndexCount = 2;
    swapchain_info.pQueueFamilyIndices = queue_family_indices;
  } else {
    swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  }
  
  swapchain_info.preTransform = support.capabilities.currentTransform;
  swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swapchain_info.presentMode = support.present_mode;
  swapchain_info.clipped = VK_TRUE;
  swapchain_info.oldSwapchain = VK_NULL_HANDLE;
  
  VK_ASSERT(vkCreateSwapchainKHR(device, &swapchain_info, allocator, &swapchain));
}

void Swapchain::DestroySwapchain() {
}

}
