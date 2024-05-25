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
    create_info.instance->CreateDevice(surface);
  }
  else {
    FL_LOG_WARN("Creating more window surfaces after the first is not guaranteed to work...");
    FL_ASSERT(Instance::CheckDeviceSuitability(create_info.instance->physical_device, surface));
  }

  swapchain = new Swapchain();
  
  FL_LOG_TRACE("Vulkan WindowSurface Created");
}

WindowSurface::~WindowSurface() {
  delete swapchain;
  vkDestroySurfaceKHR(instance, surface, allocator);
  FL_LOG_TRACE("Vulkan WindowSurface Destroyed");
}

}

