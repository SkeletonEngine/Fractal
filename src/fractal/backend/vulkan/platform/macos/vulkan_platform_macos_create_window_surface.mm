#import "fractal/backend/vulkan/surface/vulkan_platform_create_window_surface.hpp"

#import <Cocoa/Cocoa.h>
#import <volk.h>

#import "fractal/backend/vulkan/common/vulkan_assert.hpp"
#import "fractal/backend/vulkan/instance/vulkan_instance_data.hpp"

typedef VkFlags VkMetalSurfaceCreateFlagsEXT;

typedef struct VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    const void*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    const void*                     pLayer;
} VkMetalSurfaceCreateInfoEXT;

typedef VkResult (*PFN_vkCreateMetalSurfaceEXT)(VkInstance, const VkMetalSurfaceCreateInfoEXT*, const VkAllocationCallbacks*, VkSurfaceKHR*);

namespace Fractal {

VkSurfaceKHR CreatePlatformWindowVkSurfaceKHR(InstanceData* instance, const WindowHandle& window_handle) {
  FL_ASSERT(window_handle);
  
  NSBundle* bundle = [NSBundle bundleWithPath:@"/System/Library/Frameworks/QuartzCore.framework"];
  if (!bundle) {
    FL_LOG_ERROR("Cocoa: Failed to find QuartzCore.framework");
    VK_ASSERT(VK_ERROR_EXTENSION_NOT_PRESENT);
  }
  
  id layer = [[bundle classNamed:@"CAMetalLayer"] layer];
  if (!layer) {
    FL_LOG_ERROR("Cocoa: Failed to create layer for view");
    VK_ASSERT(VK_ERROR_EXTENSION_NOT_PRESENT);
  }
  
  PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT = (PFN_vkCreateMetalSurfaceEXT)vkGetInstanceProcAddr(instance->instance, "vkCreateMetalSurfaceEXT");
  if (!vkCreateMetalSurfaceEXT) {
    FL_LOG_ERROR("Cocoa: Vulkan instance missing VK_EXT_metal_surface extension");
    VK_ASSERT(VK_ERROR_EXTENSION_NOT_PRESENT);
  }
  
  VkMetalSurfaceCreateInfoEXT surface_info { VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT };
  surface_info.pLayer = layer;
  
  VkSurfaceKHR surface;
  VK_CHECK(vkCreateMetalSurfaceEXT(instance->instance, &surface_info, instance->allocator, &surface));
  return surface;
}

}
