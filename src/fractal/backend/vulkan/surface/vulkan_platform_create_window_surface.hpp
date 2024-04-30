#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/surface/window_handle.hpp"
#include "fractal/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Fractal {

VkSurfaceKHR CreatePlatformWindowVkSurfaceKHR(InstanceData* instance, const WindowHandle& window_handle);

}
