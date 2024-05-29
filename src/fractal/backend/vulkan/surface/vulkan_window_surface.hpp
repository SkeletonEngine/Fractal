#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/platform/window_handle.hpp"
#include "fractal/base/surface/window_surface_create_info.hpp"
#include "fractal/backend/vulkan/instance/vulkan_instance.hpp"
#include "fractal/backend/vulkan/swapchain/vulkan_swapchain.hpp"

namespace Fractal {

class WindowSurface {
public:
  WindowSurface(const WindowSurfaceCreateInfo& create_info);
  ~WindowSurface();
  
private:
  void CreatePlatformWindowVkSurfaceKHR(const WindowHandle& window_handle);

private:
  // Non-owning pointers
  VkInstance instance;
  VkAllocationCallbacks* allocator;

  // Owned by this class
  Swapchain* swapchain;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
};

}
