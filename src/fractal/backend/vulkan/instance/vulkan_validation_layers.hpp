#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#ifdef FL_BUILD_DEBUG

struct VkInstanceCreateInfo;
struct VkDebugUtilsMessengerCreateInfoEXT;
struct VkDeviceCreateInfo;

namespace Fractal {

void ListValidationLayerSupport();
bool CheckValidationLayerSupport();
void PopulateValidationLayers(VkInstanceCreateInfo& instance_info);
void PopulateDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debug_messenger_info);
void CreateDebugMessenger(VkInstance instance, VkAllocationCallbacks* allocator);
void PopulateDeviceValidationLayers(VkDeviceCreateInfo& device_info);

}

#endif
