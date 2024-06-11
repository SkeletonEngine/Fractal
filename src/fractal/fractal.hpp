#pragma once

#ifdef FRACTAL_BACKEND_NULL
  #include "fractal/backend/null/instance/null_instance.hpp"
  #include "fractal/backend/null/surface/null_window_surface.hpp"
  #include "fractal/backend/null/shader/null_shader.hpp"
#endif

#ifdef FRACTAL_BACKEND_VULKAN
  #include "fractal/backend/vulkan/instance/vulkan_instance.hpp"
  #include "fractal/backend/vulkan/surface/vulkan_window_surface.hpp"
  #include "fractal/backend/vulkan/render_pass/vulkan_render_pass.hpp"
  #include "fractal/backend/vulkan/shader/vulkan_shader.hpp"
#endif
