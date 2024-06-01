#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

namespace Fractal {

class QueueFamilyIndices {
public:
  QueueFamilyIndices(VkPhysicalDevice physical_device, VkSurfaceKHR surface);

public:
  uint32_t GetGraphicsFamily() const;
  uint32_t GetPresentFamily() const;

  bool IsComplete() const;

private:
  uint32_t graphics_family = -1;
  uint32_t present_family  = -1;
};

}
