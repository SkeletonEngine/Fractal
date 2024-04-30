#include "fractal/base/surface/window_surface.hpp"
#include "fractal/base/common/base.hpp"

#include "fractal/backend/null/instance/null_instance_data.hpp"

namespace Fractal {

struct WindowSurface::Data {
  InstanceData* instance;
};

WindowSurface::WindowSurface(const WindowSurfaceCreateInfo& create_info) {
  data = new WindowSurface::Data();
  data->instance = create_info.instance->instance;
  FL_LOG_TRACE("Null WindowSurface created");
}

WindowSurface::~WindowSurface() {
  FL_LOG_TRACE("Null WindowSurface destroyed");
  delete data;
}

}
