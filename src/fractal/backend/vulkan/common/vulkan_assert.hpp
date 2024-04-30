#pragma once

#include "fractal/base/common/platform.hpp"

#ifdef FL_BUILD_DEBUG
  #define VK_NO_PROTOTYPES
  #include <vulkan/vk_enum_string_helper.h>
  #include "fractal/base/common/assert.hpp"

  #define FL_CONCAT(x, y) x##y

  #define VK_ASSERT(x) { VkResult FL_CONCAT(result, __LINE__) = x; if (FL_CONCAT(result, __LINE__) != VK_SUCCESS) { FL_LOG_ERROR("VK_ASSERT failed: {}", #x); FL_DEBUGBREAK(); } }
  #define VK_CHECK(x)  { VkResult FL_CONCAT(result, __LINE__) = x; if (FL_CONCAT(result, __LINE__) != VK_SUCCESS) { FL_LOG_ERROR("VK_CHECK failed: {}", #x);  FL_DEBUGBREAK(); } }

#else

  #define VK_ASSERT(x)
  #define VK_CHECK(x) x

#endif
