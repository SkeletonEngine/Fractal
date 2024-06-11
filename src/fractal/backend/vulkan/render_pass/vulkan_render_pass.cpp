#include "fractal/backend/vulkan/render_pass/vulkan_render_pass.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include <volk.h>

#include "fractal/backend/vulkan/surface/vulkan_window_surface.hpp"

namespace Fractal {

constexpr VkAttachmentLoadOp FindLoadOp(RenderPassBeginOp op) {
  switch (op) {
    case RenderPassBeginOp::kClear:    return VK_ATTACHMENT_LOAD_OP_CLEAR;
    case RenderPassBeginOp::kPreserve: return VK_ATTACHMENT_LOAD_OP_LOAD;
  }
}

constexpr VkAttachmentStoreOp FindStoreOp(RenderPassEndOp op) {
  switch (op) {
    case RenderPassEndOp::kPreserve:    return VK_ATTACHMENT_STORE_OP_STORE;
    case RenderPassEndOp::kSwapBuffers: return VK_ATTACHMENT_STORE_OP_STORE;
  }
}

constexpr VkImageLayout FindInitialLayout(RenderPassBeginOp op) {
  switch (op) {
    case RenderPassBeginOp::kClear:    return VK_IMAGE_LAYOUT_UNDEFINED;
    case RenderPassBeginOp::kPreserve: return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; // TODO: ?
  }
}

constexpr VkImageLayout FindFinalLayout(RenderPassEndOp op) {
  switch (op) {
    case RenderPassEndOp::kPreserve:    return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; // TODO: ?
    case RenderPassEndOp::kSwapBuffers: return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
  }
}

RenderPass::RenderPass(const RenderPassCreateInfo& create_info) {
  device = create_info.surface->device;
  allocator = create_info.surface->allocator;
  
  VkAttachmentDescription color_attachment { };
  color_attachment.format = create_info.surface->swapchain.image_format;
  color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  color_attachment.loadOp = FindLoadOp(create_info.begin_op);
  color_attachment.storeOp = FindStoreOp(create_info.end_op);
  color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_attachment.initialLayout = FindInitialLayout(create_info.begin_op);
  color_attachment.finalLayout = FindFinalLayout(create_info.end_op);
  
  VkAttachmentReference color_attachment_ref { };
  color_attachment_ref.attachment = 0;
  color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  
  VkSubpassDescription subpass_desc { };
  subpass_desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_desc.colorAttachmentCount = 1;
  subpass_desc.pColorAttachments = &color_attachment_ref;
  
  VkRenderPassCreateInfo render_pass_info { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
  render_pass_info.attachmentCount = 1;
  render_pass_info.pAttachments = &color_attachment;
  render_pass_info.subpassCount = 1;
  render_pass_info.pSubpasses = &subpass_desc;
  
  VK_CHECK(vkCreateRenderPass(device, &render_pass_info, allocator, &render_pass));
  
  FL_LOG_TRACE("Vulkan RenderPass created");
}

RenderPass::~RenderPass() {
  vkDestroyRenderPass(device, render_pass, allocator);
  
  FL_LOG_TRACE("Vulkan RenderPass destroyed");
}

}
