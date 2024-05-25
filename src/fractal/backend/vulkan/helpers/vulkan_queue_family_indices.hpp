#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

namespace Fractal {

class VulkanQueueFamilyIndices {
public:
  VulkanQueueFamilyIndices(VkPhysicalDevice physical_device, VkSurfaceKHR surface);

public:
  int GetGraphicsFamily() const;
  int GetPresentFamily() const;

  bool IsComplete() const;

private:
  int graphics_family = -1;
  int present_family  = -1;
};

}
