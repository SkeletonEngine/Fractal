#include "fractal./backend/null/surface/null_window_surface.hpp"
#include "fractal/base/common/base.hpp"

namespace Fractal {

WindowSurface::WindowSurface(const WindowSurfaceCreateInfo& create_info) {
  FL_LOG_TRACE("Null WindowSurface created");
}

WindowSurface::~WindowSurface() {
  FL_LOG_TRACE("Null WindowSurface destroyed");
}

}
