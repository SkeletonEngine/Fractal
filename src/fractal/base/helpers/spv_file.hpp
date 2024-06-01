#pragma once
#include "fractal/base/common/base.hpp"

namespace Fractal {

class SpvFile {
public:
  SpvFile(const char* path);
  ~SpvFile();
  
private:
  char* code;
  size_t code_size;
};

}
