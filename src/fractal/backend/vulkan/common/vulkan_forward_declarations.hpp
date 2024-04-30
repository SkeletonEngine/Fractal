#pragma once

#define VK_DEFINE_HANDLE(object) typedef struct object##_T* object;

struct VkAllocationCallbacks;

VK_DEFINE_HANDLE(VkInstance);
VK_DEFINE_HANDLE(VkPhysicalDevice);
VK_DEFINE_HANDLE(VkSurfaceKHR);
VK_DEFINE_HANDLE(VkDebugUtilsMessengerEXT);
VK_DEFINE_HANDLE(VkDevice);
VK_DEFINE_HANDLE(VkQueue);
