#pragma once
#include "fractal/base/common/base.hpp"

#ifdef FL_PLATFORM_WINDOWS
  #include "fractal/base/platform/windows/windows_forward_declarations.hpp"
#endif

#ifdef FL_PLATFORM_MACOS
#include "fractal/base/platform/macos/macos_forward_declarations.hpp"
#endif

#include <glm/glm.hpp>

namespace Fractal {

class WindowHandle {
public:
  WindowHandle() = default;

#ifdef FL_PLATFORM_WINDOWS
  WindowHandle(HWND hwnd);
#endif

#ifdef FL_PLATFORM_MACOS
  WindowHandle(NsView nsview);
#endif

public:
  glm::ivec2 GetFramebufferExtent() const;

private:
#ifdef FL_PLATFORM_WINDOWS
  HWND hwnd;
#endif
  
#ifdef FL_PLATFORM_MACOS
  NsView nsview;
#endif

private:
  friend class WindowSurface;
};

}

