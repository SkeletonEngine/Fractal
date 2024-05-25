#pragma once

#include "fractal/base/surface/window_handle.hpp"

namespace Fractal {

class Instance;

struct WindowSurfaceCreateInfo {
  Instance* instance;
  WindowHandle window_handle;
};

}
