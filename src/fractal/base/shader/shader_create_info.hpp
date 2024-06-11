#pragma once

namespace Fractal {

class Instance;
class WindowSurface;

struct ShaderCreateInfo {
  Instance* instance     = nullptr;
  WindowSurface* surface = nullptr;
  const char* vert_path  = nullptr;
  const char* frag_path  = nullptr;
};

}
