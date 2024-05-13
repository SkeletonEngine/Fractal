#pragma once

#include "fractal/base/platform/macos/macos_forward_declarations.hpp"

namespace Fractal::Example {

class CocoaWindow {
public:
  CocoaWindow();
  ~CocoaWindow();
  
public:
  bool IsOpen() const;
  void PollEvents();

public:
  inline NsView GetNSView() const {
    return nsview;
  }

private:
  NsView nsview = 0;

public:
  void SetShouldClose() {
    should_close = true;
  }
  
private:
  bool should_close = false;
};

}
