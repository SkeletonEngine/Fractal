#pragma once
#include "fractal/base/common/base.hpp"

#include "fractal/base/surface/window_handle.hpp"
#include "fractal/backend/vulkan/instance/vulkan_instance.hpp"
#include "fractal/backend/vulkan/swapchain/vulkan_swapchain.hpp"

namespace Fractal {

struct WindowSurfaceCreateInfo {
  Instance* instance;
  WindowHandle window_handle;
};

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
  Swapchain* swapchain = nullptr;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
};

}
