#pragma once

#ifdef FRACTAL_BACKEND_NULL
  #include "fractal/backend/null/instance/null_instance.hpp"
  #include "fractal/backend/null/surface/null_window_surface.hpp"
#endif

#ifdef FRACTAL_BACKEND_VULKAN
  #include "fractal/backend/vulkan/instance/vulkan_instance.hpp"
  #include "fractal/backend/vulkan/surface/vulkan_window_surface.hpp"
#endif