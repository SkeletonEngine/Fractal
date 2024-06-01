#pragma once

#include "fractal/base/platform/window_handle.hpp"

namespace Fractal {

class Instance;

struct WindowSurfaceCreateInfo {
  Instance* instance;
  WindowHandle window_handle;
};

}
