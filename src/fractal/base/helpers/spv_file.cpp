#include "fractal/base/helpers/spv_file.hpp"
#include "fractal/base/common/base.hpp"

#include <fstream>

namespace Fractal {

SpvFile::SpvFile(const char* path) {
  std::ifstream file(path, std::ios::ate | std::ios::binary);
  FL_ASSERT(file.is_open());
  code_size = (size_t)file.tellg();
  code = new char[code_size];
  file.seekg(0);
  file.read(code, code_size);
}

SpvFile::~SpvFile() {
  delete code;
}

const char* SpvFile::GetCode() const {
  return code;
}

size_t SpvFile::GetCodeSize() const {
  return code_size;
}

}

