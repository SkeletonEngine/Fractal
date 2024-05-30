#import "fractal/base/platform/window_handle.hpp"

#import <Cocoa/Cocoa.h>

namespace Fractal {

WindowHandle::WindowHandle(NsView nsview) : nsview(nsview) {
  FL_ASSERT(nsview);
}

glm::ivec2 WindowHandle::GetFramebufferExtent() const {
  NSRect rect = [nsview bounds];
  return glm::ivec2(rect.size.width, rect.size.height);
}

}
