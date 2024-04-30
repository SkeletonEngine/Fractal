#include "vulkan_validation_layers.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#ifdef FL_BUILD_DEBUG

#include <volk.h>

namespace Fractal {

VkDebugUtilsMessengerEXT debug_messenger = VK_NULL_HANDLE;

static const char* const kRequiredValidationLayers[] = {
  "VK_LAYER_KHRONOS_validation",
};

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data) {

  switch (message_severity) {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
      FL_LOG_TRACE("Validation layer: {0}", callback_data->pMessage);
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
      FL_LOG_INFO("Validation layer: {0}", callback_data->pMessage);
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
      FL_LOG_WARN("Validation layer: {0}", callback_data->pMessage);
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
      FL_LOG_ERROR("Validation layer: {0}", callback_data->pMessage);
      break;
    default: break;
  }

  return VK_FALSE;
}

void ListValidationLayerSupport() {
  FL_LOG_TRACE("Listing supported Vulkan validation layers...");

  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
  std::vector<VkLayerProperties> available_layers(layer_count);
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

  for (auto& props : available_layers) {
    FL_LOG_TRACE("  > {}", props.layerName);
  }
}

bool CheckValidationLayerSupport() {
  uint32_t layer_count = 0;
  vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
  std::vector<VkLayerProperties> available_layers(layer_count);
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());
  
  for (size_t i = 0; i < FL_ARRAYSIZE(kRequiredValidationLayers); ++i) {
    bool found = false;
  
    for (const auto& props : available_layers) {
      if (strcmp(kRequiredValidationLayers[i], props.layerName) == 0) {
        found = true;
        break;
      }
    }
  
    if (!found) {
      FL_LOG_ERROR("Vulkan validation layer {} requested but not found", kRequiredValidationLayers[i]);
      return false;
    }
  }

  return true;
}

void PopulateValidationLayers(VkInstanceCreateInfo& instance_info) {
  instance_info.enabledLayerCount = FL_ARRAYSIZE(kRequiredValidationLayers);
  instance_info.ppEnabledLayerNames = kRequiredValidationLayers;
}

void PopulateDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debug_messenger_info) {
  debug_messenger_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  debug_messenger_info.messageSeverity
    = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT 
    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT 
    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  debug_messenger_info.messageType
    = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  debug_messenger_info.pfnUserCallback = DebugCallback;
}

void CreateDebugMessenger(VkInstance instance, VkAllocationCallbacks* allocator) {
  VkDebugUtilsMessengerCreateInfoEXT debug_messenger_info { };
  PopulateDebugUtilsMessengerCreateInfo(debug_messenger_info);

  VK_CHECK(vkCreateDebugUtilsMessengerEXT(instance, &debug_messenger_info, allocator, &debug_messenger));
}

void PopulateDeviceValidationLayers(VkDeviceCreateInfo& device_info) {
  device_info.enabledLayerCount = FL_ARRAYSIZE(kRequiredValidationLayers);
  device_info.ppEnabledLayerNames = kRequiredValidationLayers;
}

}

#endif // FL_BUILD_DEBUG
