#pragma once
#include "fractal/base/common/base.hpp"

#ifdef FL_PLATFORM_WINDOWS
  #include "fractal/base/platform/windows/windows_forward_declarations.hpp"
#endif

#ifdef FL_PLATFORM_MACOS
#include "fractal/base/platform/macos/macos_forward_declarations.hpp"
#endif

namespace Fractal {

struct WindowHandle {
  
#ifdef FL_PLATFORM_WINDOWS
  HWND hwnd = nullptr;
#endif
  
#ifdef FL_PLATFORM_MACOS
  NsView nsview = nullptr;
#endif
  
};

}
