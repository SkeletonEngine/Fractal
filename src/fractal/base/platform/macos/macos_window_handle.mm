#import "fractal/base/platform/window_handle.hpp"

#import <Cocoa/Cocoa.h>

namespace Fractal {

glm::ivec2 GetWindowFramebufferExtent(const WindowHandle& window) {
  NSRect rect = [window bounds];
  
  return glm::ivec2(1.0f);
}

}
