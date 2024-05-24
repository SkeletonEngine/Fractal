#include "vulkan_device.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <set>
#include <vector>

#include <volk.h>

#include "fractal/backend/vulkan/instance/vulkan_queue_family_indices.hpp"
#include "fractal/backend/vulkan/instance/vulkan_validation_layers.hpp"
#include "fractal/backend/vulkan/instance/vulkan_instance_data.hpp"
#include "fractal/backend/vulkan/surface/vulkan_swapchain_support_details.hpp"

namespace Fractal {

static const char* const kRequiredDeviceExtensions[] = {
  "VK_KHR_swapchain",

#ifdef FL_PLATFORM_MACOS
  "VK_KHR_portability_subset",
#endif
};

static void ListDeviceExtensionSupport(VkPhysicalDevice device) {
  FL_LOG_TRACE("Listing supported Vulkan device extensions...");

  uint32_t extension_count = 0;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);
  std::vector<VkExtensionProperties> extensions(extension_count);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, extensions.data());

  size_t supported_extension_count = 0;

  for (auto& ep : extensions) {
    FL_LOG_TRACE("  > {}", ep.extensionName);
  }
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

bool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
  VulkanQueueFamilyIndices indices(device, surface);
  VulkanSwapchainSupportDetails swapchain_support(device, surface);
  
  return CheckDeviceExtensionSupport(device) && indices.IsComplete() && swapchain_support.IsSuitable();
}

static int RatePhysicalDevice(VkPhysicalDevice device, VkSurfaceKHR surface) {
  VkPhysicalDeviceProperties device_properties;
  vkGetPhysicalDeviceProperties(device, &device_properties);

  if (!IsDeviceSuitable(device, surface)) {
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

  // Anisotropy is an optional but nice to have feature
  VkPhysicalDeviceFeatures device_features { };
  vkGetPhysicalDeviceFeatures(device, &device_features);
  if (device_features.samplerAnisotropy) {
    score += 300;
  }

  return score;
}

static void ChoosePhysicalDevice(InstanceData* instance, VkSurfaceKHR surface) {
  uint32_t device_count = 0;
  vkEnumeratePhysicalDevices(instance->instance, &device_count, nullptr);

  FL_ASSERT(device_count > 0);

  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(instance->instance, &device_count, devices.data());

  int highest_score = 0;
  for (auto device : devices) {
    int current_score = RatePhysicalDevice(device, surface);
    if (current_score > highest_score) {
      highest_score = current_score;
      instance->physical_device = device;
    }
  }

  FL_ASSERT(highest_score > 0);

  VkPhysicalDeviceProperties props { };
  vkGetPhysicalDeviceProperties(instance->physical_device, &props);
  FL_LOG_INFO("Vulkan Device: {}", props.deviceName);
}

void CreateDevice(InstanceData* instance, VkSurfaceKHR surface) {
  ChoosePhysicalDevice(instance, surface);

  VkPhysicalDeviceFeatures device_features { };

  VulkanQueueFamilyIndices indices(instance->physical_device, surface);
  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  std::set<int> unique_queue_families = { indices.GetGraphicsFamily(), indices.GetPresentFamily() };
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
  PopulateDeviceValidationLayers(device_info);
#endif

  VK_CHECK(vkCreateDevice(instance->physical_device, &device_info, instance->allocator, &instance->device));
  vkGetDeviceQueue(instance->device, indices.GetGraphicsFamily(), 0, &instance->graphics_queue);
  vkGetDeviceQueue(instance->device, indices.GetPresentFamily(),  0, &instance->present_queue);
  
  FL_LOG_TRACE("Vulkan Device created");
  FL_DEBUG_ONLY(ListDeviceExtensionSupport(instance->physical_device));
}

}
