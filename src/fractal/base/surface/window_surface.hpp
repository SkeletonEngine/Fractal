#pragma once
#include "fractal/base/common/base.hpp"

#include "fractal/base/instance/instance.hpp"
#include "fractal/base/surface/window_handle.hpp"

namespace Fractal {

struct WindowSurfaceCreateInfo {
  Instance* instance;
  WindowHandle window_handle;
};

struct WindowSurfaceData;

class WindowSurface {
public:
  WindowSurface(const WindowSurfaceCreateInfo& create_info);
  ~WindowSurface();
  
private:
  WindowSurfaceData* data;
};

}
