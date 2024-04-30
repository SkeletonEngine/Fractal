#pragma once

#ifndef NDEBUG
	#define FL_BUILD_DEBUG
#else
	#define FL_BUILD_RELEASE
#endif

#ifdef _WIN32
	#define FL_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define FL_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define FL_PLATFORM_MACOS
	#else
		#error "Unable to determine Apple platform"
	#endif
#elif defined(__ANDROID__)
	#define FL_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define FL_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unable to determine platform"
#endif

#ifdef FL_BUILD_DEBUG
  #define FL_DEBUG_ONLY(x) x
#else
  #define FL_DEBUG_ONLY(x)
#endif
