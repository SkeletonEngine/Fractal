#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

namespace Fractal {

class Swapchain {
public:
  Swapchain();

private:
  void CreateSwapchain();
};

}
