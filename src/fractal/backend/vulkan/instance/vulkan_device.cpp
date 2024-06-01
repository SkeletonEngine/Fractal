#include "fractal/backend/vulkan/instance/vulkan_instance.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <set>
#include <sstream>
#include <vector>

#include <volk.h>

#include "fractal/backend/vulkan/helpers/vulkan_queue_family_indices.hpp"
#include "fractal/backend/vulkan/helpers/vulkan_swapchain_support_details.hpp"

namespace Fractal {

static const char* const kRequiredDeviceExtensions[] = {
  "VK_KHR_swapchain",

#ifdef FL_PLATFORM_MACOS
  "VK_KHR_portability_subset",
#endif
};

static void ListDeviceExtensionSupport(VkPhysicalDevice device) {
  uint32_t extension_count = 0;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());

  std::stringstream ss;
  for (int i = 0; i < extension_count; ++i) {
    ss << available_extensions[i].extensionName;
    if (i < extension_count - 1) ss << ", ";
  }
  FL_LOG_TRACE("Available device extensions: [{}]", ss.str());
}

static bool CheckDeviceExtensionSupport(VkPhysicalDevice device) {
  uint32_t extension_count = 0;
  vkEnumerateDeviceExtensionProperties(device,nullptr, &extension_count, nullptr);
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());
  
  for (size_t i = 0; i < FL_ARRAYSIZE(kRequiredDeviceExtensions); ++i) {
    bool found = false;
  
    for (const auto& props : available_extensions) {
      if (strcmp(kRequiredDeviceExtensions[i], props.extensionName) == 0) {
        found = true;
        break;
      }
    }
  
    if (!found) {
      FL_LOG_ERROR("Vulkan device extension {} requested but not found", kRequiredDeviceExtensions[i]);
      return false;
    }
  }

  return true;
}

static void PopulateDeviceExtensions(VkDeviceCreateInfo& device_info) {
  device_info.ppEnabledExtensionNames = kRequiredDeviceExtensions;
  device_info.enabledExtensionCount = FL_ARRAYSIZE(kRequiredDeviceExtensions);
}

bool Instance::CheckDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface, WindowHandle window) {
  QueueFamilyIndices indices(device, surface);
  SwapchainSupportDetails swapchain_support(device, surface, window);
  
  return CheckDeviceExtensionSupport(device) && indices.IsComplete() && swapchain_support.IsSuitable();
}

int Instance::RatePhysicalDevice(VkPhysicalDevice device, VkSurfaceKHR surface, WindowHandle window) {
  VkPhysicalDeviceProperties device_properties;
  vkGetPhysicalDeviceProperties(device, &device_properties);

  if (!Instance::CheckDeviceSuitability(device, surface, window)) {
    return 0;
  }

  // Device is suitable. Now allocate it a score
  int score = 0;

  // Prioritize discrete GPUs
  if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
    score += 1000;
  }
  
  // Prioritize devices that support larger textures
  score += device_properties.limits.maxImageDimension2D / 100;

  // Prioritize devices with more memory
  VkPhysicalDeviceMemoryProperties memory_props { };
  vkGetPhysicalDeviceMemoryProperties(device, &memory_props);
  for (size_t i = 0; i < memory_props.memoryHeapCount; ++i) {
    score += (int)memory_props.memoryHeaps[i].size / 10000000;
  }

  // Anisotropy is an optional feature but nice to have
  VkPhysicalDeviceFeatures device_features { };
  vkGetPhysicalDeviceFeatures(device, &device_features);
  if (device_features.samplerAnisotropy) {
    score += 300;
  }

  return score;
}

void Instance::ChoosePhysicalDevice(VkSurfaceKHR surface, WindowHandle window) {
  uint32_t device_count = 0;
  vkEnumeratePhysicalDevices(instance, &device_count, nullptr);
  FL_ASSERT(device_count > 0);

  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

  int highest_score = 0;
  for (auto device : devices) {
    int current_score = RatePhysicalDevice(device, surface, window);
    if (current_score > highest_score) {
      highest_score = current_score;
      physical_device = device;
    }
  }

  FL_ASSERT(highest_score > 0);

  VkPhysicalDeviceProperties props { };
  vkGetPhysicalDeviceProperties(physical_device, &props);
  FL_LOG_INFO("Vulkan Device: {}", props.deviceName);
}

void Instance::CreateDevice(VkSurfaceKHR surface, WindowHandle window) {
  ChoosePhysicalDevice(surface, window);

  VkPhysicalDeviceFeatures device_features { };

  QueueFamilyIndices indices(physical_device, surface);
  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  std::set<uint32_t> unique_queue_families = { indices.GetGraphicsFamily(), indices.GetPresentFamily() };
  float queue_priority = 1.0f;
  for (int queue_family : unique_queue_families) {
    VkDeviceQueueCreateInfo queue_create_info { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
    queue_create_info.queueFamilyIndex = queue_family;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;
    queue_create_infos.push_back(queue_create_info);
  }

  VkDeviceCreateInfo device_info { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
  device_info.pQueueCreateInfos = queue_create_infos.data();
  device_info.queueCreateInfoCount = (uint32_t)queue_create_infos.size();
  device_info.pEnabledFeatures = &device_features;
  
  PopulateDeviceExtensions(device_info);
#ifdef FL_BUILD_DEBUG
  Instance::PopulateDeviceCreateInfoValidationLayers(device_info);
#endif

  VK_CHECK(vkCreateDevice(physical_device, &device_info, allocator, &device));
  vkGetDeviceQueue(device, indices.GetGraphicsFamily(), 0, &graphics_queue);
  vkGetDeviceQueue(device, indices.GetPresentFamily(),  0, &present_queue);
  
  FL_LOG_TRACE("Vulkan Device created");
  FL_DEBUG_ONLY(ListDeviceExtensionSupport(physical_device));
}

}
