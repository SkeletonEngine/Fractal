#pragma once

#include "fractal/base/platform/windows/windows_forward_declarations.hpp"

namespace Fractal::Example {

class Win32Window {
public:
  Win32Window();
  ~Win32Window();

public:
  bool IsOpen() const;
  void PollEvents();

private:
  HWND hwnd = nullptr;

public:
  inline HWND GetHwnd() const {
    return hwnd;
  };

};

}
