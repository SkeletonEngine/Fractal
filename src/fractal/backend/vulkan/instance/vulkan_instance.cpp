#include "fractal/backend/vulkan/instance/vulkan_instance.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

namespace Fractal {

Instance::Instance(const InstanceCreateInfo& create_info) {
  if (create_info.logger_callback) {
    Internal::SetGlobalLoggerCallback(create_info.logger_callback);
  }

  VK_CHECK(volkInitialize());
  
  FL_DEBUG_ONLY(ListValidationLayerSupport());
  FL_ASSERT(CheckValidationLayerSupport());
  FL_DEBUG_ONLY(ListInstanceExtensionSupport());
  FL_ASSERT(CheckInstanceExtensionSupport());

  VkApplicationInfo app_info { VK_STRUCTURE_TYPE_APPLICATION_INFO };
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instance_info { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
#ifdef FL_BUILD_DEBUG
  PopulateInstanceCreateInfoValidationLayers(instance_info);
  VkDebugUtilsMessengerCreateInfoEXT debug_messenger_info { };
  PopulateDebugUtilsMessengerCreateInfo(debug_messenger_info);
  instance_info.pNext = &debug_messenger_info;
#endif
  instance_info.pApplicationInfo = &app_info;
  PopulateInstanceCreateInfoEnabledExtensions(instance_info);
  
  VK_CHECK(vkCreateInstance(&instance_info, allocator, &instance));
  volkLoadInstance(instance); // TODO: Either explicitly support multiple instances or don't

#ifdef FL_BUILD_DEBUG
  CreateDebugMessenger();
  FL_ASSERT(debug_messenger);
#endif
  
  FL_LOG_TRACE("Vulkan Instance created");
}

Instance::~Instance() {
  if (device) {
    vkDestroyDevice(device, allocator);
  }
  FL_DEBUG_ONLY(vkDestroyDebugUtilsMessengerEXT(instance, debug_messenger, allocator));
  vkDestroyInstance(instance, allocator);
  FL_LOG_TRACE("Vulkan Instance destroyed");
}

}

