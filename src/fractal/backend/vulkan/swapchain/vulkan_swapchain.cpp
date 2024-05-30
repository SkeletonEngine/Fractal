#include "vulkan_swapchain.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/backend/vulkan/helpers/vulkan_swapchain_support_details.hpp"

namespace Fractal {

Swapchain::Swapchain(VkPhysicalDevice device, VkSurfaceKHR surface, const WindowHandle& window)
  : device(device), surface(surface), window(window) {
    CreateSwapchain();
}

void Swapchain::CreateSwapchain() {
  VulkanSwapchainSupportDetails support(device, surface, window);
}

void Swapchain::DestroySwapchain() {
}

}
