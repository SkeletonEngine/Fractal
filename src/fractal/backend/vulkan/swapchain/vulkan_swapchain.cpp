#include "vulkan_swapchain.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

#include "fractal/backend/vulkan/helpers/vulkan_swapchain_support_details.hpp"
#include "fractal/backend/vulkan/helpers/vulkan_queue_family_indices.hpp"

namespace Fractal {

void Swapchain::SetupSwapchain(VkDevice device, VkPhysicalDevice physical_device, VkAllocationCallbacks* allocator, VkSurfaceKHR surface, WindowHandle window) {
  this->device = device;
  this->physical_device = physical_device;
  this->allocator = allocator;
  this->surface = surface;
  this->window = window;
}

void Swapchain::CreateSwapchain() {
  SwapchainSupportDetails support(physical_device, surface, window);
  extent = support.extent;
  image_format = support.surface_format.format;
  
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
  
  QueueFamilyIndices indices(physical_device, surface);
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

  vkGetSwapchainImagesKHR(device, swapchain, &image_count, nullptr);
  images = new VkImage[image_count];
  vkGetSwapchainImagesKHR(device, swapchain, &image_count, images);

  FL_LOG_TRACE("Vulkan Swapchain created");
}

void Swapchain::DestroySwapchain() {
  delete images;
  vkDestroySwapchainKHR(device, swapchain, allocator);
  FL_LOG_TRACE("Vulkan Swapchain destroyed");
}


void Swapchain::CreateImageViews() {

}

}
