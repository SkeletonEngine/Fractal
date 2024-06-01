#include "logger.hpp"
#include "fractal/base/common/base.hpp"

#include <cstdio>
#include <ctime>
#include <format>
#include <iomanip>
#include <iostream>

namespace Fractal::Internal {

static void DefaultLoggerCallback(LoggerLevel level, const char* message) {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  
  std::cout << "[" << std::put_time(&tm, "%H:%M:%S") << "] [Fractal] [" << LoggerLevelStr(level) << "] " << message << std::endl;
}

static LoggerCallback global_logger_callback = DefaultLoggerCallback;

void SetGlobalLoggerCallback(LoggerCallback logger) {
  global_logger_callback = logger;
}

void InvokeGlobalLoggerCallback(LoggerLevel level, const char* message) {
  global_logger_callback(level, message);
}

}
