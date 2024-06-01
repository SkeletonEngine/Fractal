#include "fractal/backend/vulkan/shader/vulkan_shader.hpp"
#include "fractal/backend/vulkan/common/vulkan_base.hpp"

#include "fractal/base/helpers/spv_file.hpp"

namespace Fractal {

Shader::Shader() {
  Fractal::SpvFile vert_file("build/shaders/example.vert.glsl.spv");
  Fractal::SpvFile frag_file("build/shaders/example.frag.glsl.spv");
}

}
