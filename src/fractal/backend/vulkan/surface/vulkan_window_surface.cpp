#include "fractal/backend/vulkan/surface/vulkan_window_surface.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

#include "fractal/backend/vulkan/swapchain/vulkan_swapchain.hpp"

namespace Fractal {

WindowSurface::WindowSurface(const WindowSurfaceCreateInfo& create_info) {
  instance = create_info.instance->instance;
  allocator = create_info.instance->allocator;
  
  CreatePlatformWindowVkSurfaceKHR(create_info.window_handle);
  FL_ASSERT(surface);

  // TODO: For now we only support one GPU... This is an edge case that may be worth revisiting
  if (!create_info.instance->device) {
    create_info.instance->CreateDevice(surface, create_info.window_handle);
  }
  else {
    FL_LOG_WARN("Creating more window surfaces after the first will currently only work if all windows are compatible with the same device. Proceed with caution.");
    FL_ASSERT(Instance::CheckDeviceSuitability(create_info.instance->physical_device, surface, create_info.window_handle));
  }
  
  FL_LOG_TRACE("Vulkan WindowSurface Created");

  swapchain.SetupSwapchain(create_info.instance->device, create_info.instance->physical_device, create_info.instance->allocator, surface, create_info.window_handle);
  swapchain.CreateSwapchain();
}

WindowSurface::~WindowSurface() {
  swapchain.DestroySwapchain();
  vkDestroySurfaceKHR(instance, surface, allocator);
  FL_LOG_TRACE("Vulkan WindowSurface Destroyed");
}

}

