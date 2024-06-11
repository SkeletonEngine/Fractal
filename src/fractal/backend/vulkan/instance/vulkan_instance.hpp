#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/instance/instance_create_info.hpp"
#include "fractal/base/platform/window_handle.hpp"

namespace Fractal {

class Instance {
public:
  Instance(const InstanceCreateInfo& create_info = { });
  ~Instance();

private:
  void ChoosePhysicalDevice(VkSurfaceKHR surface, WindowHandle window);
  void CreateDevice(VkSurfaceKHR surface, WindowHandle window);
  void CreateDebugMessenger();

private:
  static void PopulateInstanceCreateInfoEnabledExtensions(VkInstanceCreateInfo& instance_info);

  static bool CheckDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface, WindowHandle window);
  static int RatePhysicalDevice(VkPhysicalDevice device, VkSurfaceKHR surface, WindowHandle window);

#ifdef FL_BUILD_DEBUG
  static void ListInstanceExtensionSupport();
  static bool CheckInstanceExtensionSupport();

  static void ListValidationLayerSupport();
  static bool CheckValidationLayerSupport();
  static void PopulateInstanceCreateInfoValidationLayers(VkInstanceCreateInfo& instance_info);
  static void PopulateDeviceCreateInfoValidationLayers(VkDeviceCreateInfo& device_info);
  static void PopulateDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debug_messenger_info);
#endif
  
private:
  VkAllocationCallbacks* allocator         = VK_NULL_HANDLE;
  VkInstance instance                      = VK_NULL_HANDLE;
  VkPhysicalDevice physical_device         = VK_NULL_HANDLE;
  VkDevice device                          = VK_NULL_HANDLE;
  VkQueue graphics_queue                   = VK_NULL_HANDLE;
  VkQueue present_queue                    = VK_NULL_HANDLE;

#ifdef FL_BUILD_DEBUG
  VkDebugUtilsMessengerEXT debug_messenger = VK_NULL_HANDLE;
#endif

private:
  friend class WindowSurface;
  friend class Shader;
};

}
