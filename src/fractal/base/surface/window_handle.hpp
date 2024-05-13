#pragma once
#include "fractal/base/common/base.hpp"

#ifdef FL_PLATFORM_WINDOWS
  #include "fractal/base/platform/windows/windows_forward_declarations.hpp"
#endif

#ifdef FL_PLATFORM_MACOS
#include "fractal/base/platform/macos/macos_forward_declarations.hpp"
#endif

namespace Fractal {
  
#ifdef FL_PLATFORM_WINDOWS
  typedef HWND WindowHandle;
#endif
  
#ifdef FL_PLATFORM_MACOS
  typedef NsView WindowHandle;
#endif

}
