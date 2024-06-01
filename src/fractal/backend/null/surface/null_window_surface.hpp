#pragma once
#include "fractal/base/common/base.hpp"

#include "fractal/base/surface/window_surface_create_info.hpp"

namespace Fractal {

class WindowSurface {
public:
  WindowSurface(const WindowSurfaceCreateInfo& create_info);
  ~WindowSurface();
};

}
