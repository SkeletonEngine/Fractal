#include "fractal/base/instance/instance.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

#include "fractal/backend/vulkan/instance/vulkan_instance_data.hpp"
#include "fractal/backend/vulkan/instance/vulkan_instance_extensions.hpp"
#include "fractal/backend/vulkan/instance/vulkan_validation_layers.hpp"

namespace Fractal {

Instance::Instance(const InstanceCreateInfo& create_info) {
  data = new InstanceData();
  VK_CHECK(volkInitialize());
  
  FL_DEBUG_ONLY(ListValidationLayerSupport());
  FL_ASSERT(CheckValidationLayerSupport());
  FL_DEBUG_ONLY(ListInstanceExtensionSupport());
  FL_ASSERT(CheckInstanceExtensionSupport());

  VkApplicationInfo app_info { VK_STRUCTURE_TYPE_APPLICATION_INFO };
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instance_info { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
#ifdef FL_BUILD_DEBUG
  PopulateValidationLayers(instance_info);
  VkDebugUtilsMessengerCreateInfoEXT debug_messenger_info { };
  PopulateDebugUtilsMessengerCreateInfo(debug_messenger_info);
  instance_info.pNext = &debug_messenger_info;
#endif
  instance_info.pApplicationInfo = &app_info;
  PopulateInstanceExtensions(instance_info);
  
  VK_CHECK(vkCreateInstance(&instance_info, data->allocator, &data->instance));
  volkLoadInstance(data->instance); // TODO: Either explicitly support multiple instances or don't

#ifdef FL_BUILD_DEBUG
  data->debug_messenger = CreateDebugMessenger(data->instance, data->allocator);
#endif
  
  FL_LOG_TRACE("Vulkan Instance Created");
}

Instance::~Instance() {
  if (data->device) {
    vkDestroyDevice(data->device, data->allocator);
  }
  if (data->debug_messenger) {
    vkDestroyDebugUtilsMessengerEXT(data->instance, data->debug_messenger, data->allocator);
  }
  if (data->instance) {
    vkDestroyInstance(data->instance, data->allocator);
  }
  delete data;
  FL_LOG_TRACE("Vulkan Instance Destroyed");
}

}

