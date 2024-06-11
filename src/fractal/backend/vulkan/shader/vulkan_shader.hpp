#pragma once
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/shader/shader_create_info.hpp"

namespace Fractal {

class Shader {
public:
  Shader(const ShaderCreateInfo& create_info);
  ~Shader();
  
private:
  VkShaderModule CreateShaderModule(const char* file_path);
  
private:
  // Non-owned objects
  VkDevice device;
  VkAllocationCallbacks* allocator;
  
  // Owned objects
  VkShaderModule vert_shader;
  VkShaderModule frag_shader;
  VkPipelineLayout pipeline_layout;
};

}
