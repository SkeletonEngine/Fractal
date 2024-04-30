#include <cstdio>

#include <fractal/fractal.hpp>

static void Logger(Fractal::LoggerLevel level, const char* message) {
  if (level >= Fractal::LoggerLevel::kInfo) {
    printf("[Fractal %s] %s\n", Fractal::LoggerLevelStr(level), message);
  }
}

int main() {
  Fractal::SetGlobalLoggerCallback(Logger);
  Fractal::Instance instance;
  Fractal::WindowSurface surface {{
    .instance = &instance,
    .window_handle {
      .hwnd = nullptr
    }
  }};
}
