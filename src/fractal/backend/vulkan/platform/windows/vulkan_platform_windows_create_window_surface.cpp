#include "fractal/backend/vulkan/surface/vulkan_window_surface.hpp"
#include "fractal/base/common/base.hpp"

#include <volk.h>
#include <Windows.h>

namespace Fractal {

void WindowSurface::CreatePlatformWindowVkSurfaceKHR(const WindowHandle& window_handle) {
  VkWin32SurfaceCreateInfoKHR surface_info { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
  surface_info.hwnd = window_handle;
  surface_info.hinstance = GetModuleHandle(nullptr);
  
  VK_CHECK(vkCreateWin32SurfaceKHR(instance, &surface_info, allocator, &surface));
}

}
