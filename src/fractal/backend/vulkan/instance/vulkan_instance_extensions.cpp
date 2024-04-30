#include "vulkan_instance_extensions.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <vector>

#include <volk.h>

namespace Fractal {

static const char* const kRequiredInstanceExtensions[] = {

  "VK_KHR_surface",

#ifdef FL_PLATFORM_WINDOWS
  "VK_KHR_win32_surface",
#endif

#ifdef FL_PLATFORM_MACOS
  "VK_EXT_metal_surface",
  "VK_KHR_portability_enumeration",
  "VK_KHR_get_physical_device_properties2",
#endif

#ifdef FL_BUILD_DEBUG
  "VK_EXT_debug_utils",
#endif

};

void ListInstanceExtensionSupport() {
  FL_LOG_TRACE("Listing supported Vulkan instance extensions...");

  uint32_t extension_count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, available_extensions.data());

  for (auto& props : available_extensions) {
    FL_LOG_TRACE("  > {}", props.extensionName);
  }
}

bool CheckInstanceExtensionSupport() {
  uint32_t extension_count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, available_extensions.data());
  
  for (size_t i = 0; i < FL_ARRAYSIZE(kRequiredInstanceExtensions); ++i) {
    bool found = false;
  
    for (const auto& props : available_extensions) {
      if (strcmp(kRequiredInstanceExtensions[i], props.extensionName) == 0) {
        found = true;
        break;
      }
    }
  
    if (!found) {
      FL_LOG_ERROR("Vulkan instance extension {} requested but not found", kRequiredInstanceExtensions[i]);
      return false;
    }
  }

  return true;
}

void PopulateInstanceExtensions(VkInstanceCreateInfo& instance_info) {
  instance_info.enabledExtensionCount = FL_ARRAYSIZE(kRequiredInstanceExtensions);
  instance_info.ppEnabledExtensionNames = kRequiredInstanceExtensions;
    
#ifdef FL_PLATFORM_MACOS
  instance_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
}

}
