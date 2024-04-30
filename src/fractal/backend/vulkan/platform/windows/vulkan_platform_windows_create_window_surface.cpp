#include "fractal/backend/vulkan/surface/vulkan_platform_create_window_surface.hpp"
#include "fractal/base/common/base.hpp"

#include <volk.h>
#include <Windows.h>

#include "fractal/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Fractal {

VkSurfaceKHR CreatePlatformWindowVkSurfaceKHR(InstanceData* instance, const WindowHandle& window_handle) {
  VkWin32SurfaceCreateInfoKHR surface_info { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
  surface_info.hwnd = window_handle.hwnd;
  surface_info.hinstance = GetModuleHandle(nullptr);
  
  VkSurfaceKHR surface;
  VK_CHECK(vkCreateWin32SurfaceKHR(instance->instance, &surface_info, instance->allocator, &surface));
  return surface;
}

}
