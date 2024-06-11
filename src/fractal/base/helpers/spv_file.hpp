#pragma once
#include "fractal/base/common/base.hpp"

namespace Fractal {

class SpvFile {
public:
  SpvFile(const char* path);
  ~SpvFile();
  
public:
  const char* GetCode() const;
  size_t GetCodeSize() const;
  
private:
  char* code;
  size_t code_size;
};

}
