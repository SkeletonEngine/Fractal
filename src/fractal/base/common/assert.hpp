#pragma once
#include "fractal/base/common/platform.hpp"

#ifdef FL_BUILD_DEBUG

	#include "fractal/base/common/logger.hpp"

	#if defined(FL_PLATFORM_WINDOWS)
		#define FL_DEBUGBREAK() __debugbreak()
	#elif defined(FL_PLATFORM_MACOS) || defined(FL_PLATFORM_LINUX)
		#include <signal.h>
		#define FL_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "FL_DEBUGBREAK is not implemented for this platform"
	#endif

  #define FL_ASSERT(x) if (!(x)) { FL_LOG_ERROR("FL_ASSERT failed: {}", #x); FL_DEBUGBREAK(); }
  #define FL_CHECK(x)  if (!(x)) { FL_LOG_ERROR("FL_CHECK failed: {}", #x);  FL_DEBUGBREAK();}

#else

	#define FL_DEBUGBREAK()
	#define FL_ASSERT(x)
	#define FL_CHECK(x) x

#endif
