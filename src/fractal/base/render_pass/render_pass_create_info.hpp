#pragma once
#include "fractal/base/common/base.hpp"

#include "fractal/base/render_pass/render_pass_begin_op.hpp"
#include "fractal/base/render_pass/render_pass_end_op.hpp"

namespace Fractal {

class WindowSurface;

struct RenderPassCreateInfo {
  WindowSurface* surface;
  RenderPassBeginOp begin_op = RenderPassBeginOp::kClear;
  RenderPassEndOp end_op = RenderPassEndOp::kSwapBuffers;
};

}
