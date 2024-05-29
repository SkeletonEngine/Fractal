#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

namespace Fractal {

class Swapchain {
public:
  void CreateSwapchain();
  void DestroySwapchain();
};

}
