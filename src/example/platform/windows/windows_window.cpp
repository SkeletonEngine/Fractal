#include "windows_window.hpp"

#include <Windows.h>

#include "fractal/base/common/assert.hpp"

namespace Fractal::Example {

Win32Window::Win32Window() {
}

Win32Window::~Win32Window() {
}

bool Win32Window::IsOpen() const {
  return true;
}

void Win32Window::PollEvents() {
}

}
