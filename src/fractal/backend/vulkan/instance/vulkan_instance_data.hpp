#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

namespace Fractal {

struct InstanceData {
  VkAllocationCallbacks* allocator         = VK_NULL_HANDLE;
  VkInstance instance                      = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT debug_messenger = VK_NULL_HANDLE;
  VkPhysicalDevice physical_device         = VK_NULL_HANDLE;
  VkDevice device                          = VK_NULL_HANDLE;
  VkQueue graphics_queue                   = VK_NULL_HANDLE;
  VkQueue present_queue                    = VK_NULL_HANDLE;
};

}
