#include "fractal/base/surface/window_surface.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

#include "fractal/backend/vulkan/surface/vulkan_window_surface_data.hpp"
#include "fractal/backend/vulkan/surface/vulkan_platform_create_window_surface.hpp"
#include "fractal/backend/vulkan/instance/vulkan_device.hpp"

namespace Fractal {

WindowSurface::WindowSurface(const WindowSurfaceCreateInfo& create_info) {
  data = new WindowSurfaceData();
  data->instance = create_info.instance->data;
  
  data->surface = CreatePlatformWindowVkSurfaceKHR(data->instance, create_info.window_handle);

  // TODO: For now we only support one GPU... This is an edge case that may be worth revisiting
  if (!data->instance->device) {
    CreateDevice(data->instance, data->surface);
  }
  else {
    FL_ASSERT(IsDeviceSuitable(data->instance->physical_device, data->surface));
  }
  
  FL_LOG_TRACE("Vulkan WindowSurface Created");
}

WindowSurface::~WindowSurface() {
  if (data->surface) {
    vkDestroySurfaceKHR(data->instance->instance, data->surface, data->instance->allocator);
  }
  delete data;
  FL_LOG_TRACE("Vulkan WindowSurface Destroyed");
}

}

