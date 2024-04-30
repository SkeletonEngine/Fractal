#include "fractal/backend/vulkan/platform/vulkan_platform_create_window_surface.hh"

#include <volk.h>
#include <Windows.h>

#include "fractal/backend/vulkan/common/vulkan_assert.hpp"
#include "fractal/backend/vulkan/instance/vulkan_instance_data.hh"

namespace Fractal {

VkSurfaceKHR CreatePlatformWindowVkSurfaceKHR(const Window& window) {
  VkWin32SurfaceCreateInfoKHR surface_info { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
  surface_info.hwnd = window.hwnd;
  surface_info.hinstance = GetModuleHandle(nullptr);
  
  VkSurfaceKHR surface;
  VK_CHECK(vkCreateWin32SurfaceKHR(instance, &surface_info, allocator, &surface));
  return surface;
}

}
