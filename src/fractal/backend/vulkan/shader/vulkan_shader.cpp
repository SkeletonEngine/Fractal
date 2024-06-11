#include "fractal/backend/vulkan/shader/vulkan_shader.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

#include "fractal/base/helpers/spv_file.hpp"
#include "fractal/backend/vulkan/instance/vulkan_instance.hpp"
#include "fractal/backend/vulkan/surface/vulkan_window_surface.hpp"

namespace Fractal {

Shader::Shader(const ShaderCreateInfo& create_info) {
  FL_ASSERT(create_info.instance);
  FL_ASSERT(create_info.surface);
  FL_ASSERT(create_info.vert_path);
  FL_ASSERT(create_info.frag_path);
  
  device = create_info.instance->device;
  allocator = create_info.instance->allocator;
  
  vert_shader = CreateShaderModule(create_info.vert_path);
  frag_shader = CreateShaderModule(create_info.frag_path);
  
  VkPipelineShaderStageCreateInfo vertex_stage_info { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
  vertex_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertex_stage_info.module = vert_shader;
  vertex_stage_info.pName = "main";
  
  VkPipelineShaderStageCreateInfo fragment_stage_info { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
  fragment_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragment_stage_info.module = frag_shader;
  fragment_stage_info.pName = "main";
  
  VkPipelineShaderStageCreateInfo shader_stage_infos[] = { vertex_stage_info, fragment_stage_info };
  
  VkDynamicState dynamic_states[] = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR,
  };
  VkPipelineDynamicStateCreateInfo dynamic_state_info { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
  dynamic_state_info.dynamicStateCount = FL_ARRAYSIZE(dynamic_states);
  dynamic_state_info.pDynamicStates = dynamic_states;
  
  VkPipelineVertexInputStateCreateInfo vertex_input_info { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
  
  VkPipelineInputAssemblyStateCreateInfo input_assembly_info { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
  input_assembly_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  input_assembly_info.primitiveRestartEnable = VK_FALSE;
  
  VkViewport viewport { };
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)create_info.surface->swapchain.extent.width;
  viewport.height = (float)create_info.surface->swapchain.extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  
  VkRect2D scissor { };
  scissor.offset = { 0, 0 };
  scissor.extent = create_info.surface->swapchain.extent;
  
  VkPipelineViewportStateCreateInfo viewport_state_info { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
  viewport_state_info.pViewports = &viewport;
  viewport_state_info.viewportCount = 1;
  viewport_state_info.pScissors = &scissor;
  viewport_state_info.scissorCount = 1;
  
  VkPipelineRasterizationStateCreateInfo rasterizer_info { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
  rasterizer_info.depthClampEnable = VK_FALSE;
  rasterizer_info.rasterizerDiscardEnable = VK_FALSE;
  rasterizer_info.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer_info.lineWidth = 1.0f;
  rasterizer_info.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer_info.depthBiasEnable = VK_FALSE;
  
  VkPipelineMultisampleStateCreateInfo multisampling_info { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
  multisampling_info.sampleShadingEnable = VK_FALSE;
  multisampling_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  
  VkPipelineColorBlendAttachmentState color_blend_attachment { };
  color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_FALSE;

  VkPipelineColorBlendStateCreateInfo color_blend_info { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
  color_blend_info.logicOpEnable = VK_FALSE;
  color_blend_info.logicOp = VK_LOGIC_OP_COPY;
  color_blend_info.attachmentCount = 1;
  color_blend_info.pAttachments = &color_blend_attachment;
  
  VkPipelineLayoutCreateInfo pipeline_layout_info { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
  VK_CHECK(vkCreatePipelineLayout(device, &pipeline_layout_info, allocator, &pipeline_layout));

  FL_LOG_TRACE("Vulkan Shader created");
}

VkShaderModule Shader::CreateShaderModule(const char* path) {
  Fractal::SpvFile spv(path);
  
  VkShaderModuleCreateInfo shader_info { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
  shader_info.codeSize = spv.GetCodeSize();
  shader_info.pCode = (uint32_t*)spv.GetCode();
  
  VkShaderModule shader;
  VK_CHECK(vkCreateShaderModule(device, &shader_info, allocator, &shader));
  return shader;
}

Shader::~Shader() {
  vkDestroyPipelineLayout(device, pipeline_layout, allocator);
  vkDestroyShaderModule(device, frag_shader, allocator);
  vkDestroyShaderModule(device, vert_shader, allocator);
  
  FL_LOG_TRACE("Vulkan Shader destroyed");
}

}
