#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/render_pass/render_pass_create_info.hpp"

namespace Fractal {

class RenderPass {
public:
  RenderPass(const RenderPassCreateInfo& create_info);
  ~RenderPass();
  
private:
  // Non-owning pointers
  VkDevice device;
  VkAllocationCallbacks* allocator;
  
  // Owned by this class
  VkRenderPass render_pass;
};

}
