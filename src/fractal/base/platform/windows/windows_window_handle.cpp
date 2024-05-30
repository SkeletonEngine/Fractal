#include "fractal/base/platform/window_handle.hpp"

#include <Windows.h>

namespace Fractal {

WindowHandle::WindowHandle(HWND hwnd) : hwnd(hwnd) {
}

glm::ivec2 WindowHandle::GetFramebufferExtent() const {
  RECT rect;
  FL_CHECK(GetClientRect(hwnd, &rect));
  int width = rect.right - rect.left;
  int height = rect.bottom - rect.top;
  return { width, height };
}

}
