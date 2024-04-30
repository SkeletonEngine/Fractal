#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Fractal {

void CreateDevice(InstanceData* instance, VkSurfaceKHR surface);
bool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

}
