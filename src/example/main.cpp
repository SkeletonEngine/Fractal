#include <cstdio>

#include <fractal/fractal.hpp>

#ifdef __APPLE__
  #include "example/platform/macos/macos_window.hpp"
#endif
#ifdef WIN32
  #include "example/platform/windows/windows_window.hpp"
#endif

static void Logger(Fractal::LoggerLevel level, const char* message) {
  if (level >= Fractal::LoggerLevel::kTrace) {
    printf("[Fractal %s] %s\n", Fractal::LoggerLevelStr(level), message);
  }
}

int main() {
#ifdef __APPLE__
  Fractal::Example::CocoaWindow window;
#endif
#ifdef WIN32
  Fractal::Example::Win32Window window;
#endif
  
  Fractal::SetGlobalLoggerCallback(Logger);
  Fractal::Instance instance;
  Fractal::WindowSurface surface {{
    .instance = &instance,

#ifdef __APPLE__
    .window_handle = window.GetNSView()
#endif
#ifdef WIN32
    .window_handle = window.GetHwnd()
#endif

  }};
  
  while (window.IsOpen()) {
    window.PollEvents();
  }
}
