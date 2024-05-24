#include "fractal/base/surface/window_surface.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

#include "fractal/backend/vulkan/instance/vulkan_device.hpp"
#include "fractal/backend/vulkan/surface/vulkan_window_surface_data.hpp"
#include "fractal/backend/vulkan/surface/vulkan_platform_create_window_surface.hpp"
#include "fractal/backend/vulkan/swapchain/vulkan_swapchain.hpp"

namespace Fractal {

WindowSurface::WindowSurface(const WindowSurfaceCreateInfo& create_info) {
  data = new WindowSurfaceData();
  data->instance = create_info.instance->data;
  
  data->surface = CreatePlatformWindowVkSurfaceKHR(data->instance, create_info.window_handle);
  FL_ASSERT(data->surface);

  // TODO: For now we only support one GPU... This is an edge case that may be worth revisiting
  if (!data->instance->device) {
    CreateDevice(data->instance, data->surface);
  }
  else {
    FL_ASSERT(IsDeviceSuitable(data->instance->physical_device, data->surface));
  }

  data->swapchain = new Swapchain();
  
  FL_LOG_TRACE("Vulkan WindowSurface Created");
}

WindowSurface::~WindowSurface() {
  delete data->swapchain;
  vkDestroySurfaceKHR(data->instance->instance, data->surface, data->instance->allocator);
  delete data;
  FL_LOG_TRACE("Vulkan WindowSurface Destroyed");
}

}

