#pragma once
#include "fractal/base/common/platform.hpp"

#include <format>

namespace Fractal {

enum class LoggerLevel {
  kNone,
  kTrace,
  kDebug,
  kInfo,
  kWarn,
  kError,
  kFatal,
  kAll,
};

constexpr const char* LoggerLevelStr(LoggerLevel level) {
  switch (level) {
    case LoggerLevel::kNone:  return "None";
    case LoggerLevel::kTrace: return "Trace";
    case LoggerLevel::kDebug: return "Debug";
    case LoggerLevel::kInfo:  return "Info";
    case LoggerLevel::kWarn:  return "Warn";
    case LoggerLevel::kError: return "Error";
    case LoggerLevel::kFatal: return "Fatal";
    case LoggerLevel::kAll:   return "All";
    default:                  return "Unknown";
  }
}

typedef void (*LoggerCallback)(LoggerLevel level, const char* message);

void SetGlobalLoggerCallback(LoggerCallback logger);

} // namespace Fractal

#ifdef FL_BUILD_DEBUG

namespace Fractal::Internal {

void InvokeGlobalLoggerCallback(LoggerLevel level, const char* message);

template<typename... Args> void InvokeGlobalLoggerCallbackWithArgs(LoggerLevel level, const char* fmt, Args&&... args) {
  InvokeGlobalLoggerCallback(level, std::vformat(fmt, std::make_format_args(args...)).c_str());
}

} // namespace Fractal::Internal

#define FL_LOG(level, fmt, ...) ::Fractal::Internal::InvokeGlobalLoggerCallbackWithArgs(level, fmt, __VA_ARGS__);

#define FL_LOG_TRACE(...) FL_LOG(LoggerLevel::kTrace, __VA_ARGS__)
#define FL_LOG_DEBUG(...) FL_LOG(LoggerLevel::kDebug, __VA_ARGS__)
#define FL_LOG_INFO(...)  FL_LOG(LoggerLevel::kInfo,  __VA_ARGS__)
#define FL_LOG_WARN(...)  FL_LOG(LoggerLevel::kWarn,  __VA_ARGS__)
#define FL_LOG_ERROR(...) FL_LOG(LoggerLevel::kError, __VA_ARGS__)
#define FL_LOG_FATAL(...) FL_LOG(LoggerLevel::kFatal, __VA_ARGS__)

#else // FL_BUILD_DEBUG

#define FL_LOG_TRACE(...)
#define FL_LOG_DEBUG(...)
#define FL_LOG_INFO(...)
#define FL_LOG_WARN(...)
#define FL_LOG_ERROR(...)
#define FL_LOG_FATAL(...)

#endif // FL_BUILD_DEBUG
