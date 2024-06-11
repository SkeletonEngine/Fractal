#include <cstdio>

#include <fractal/fractal.hpp>
#include <GLFW/glfw3.h>
#ifdef FL_PLATFORM_MACOS
  #define GLFW_EXPOSE_NATIVE_COCOA
#endif
#ifdef FL_PLATFORM_WINDOWS
  #define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>

static void LoggerFunc(Fractal::LoggerLevel level, const char* message) {
  if (level >= Fractal::LoggerLevel::kTrace) {
    printf("{level: \"%s\", message: \"%s\" }\n", Fractal::LoggerLevelStr(level), message);
  }
  if (level >= Fractal::LoggerLevel::kWarn) {
    FL_DEBUGBREAK();
  }
}

int main() {
  glfwInit();
  
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window = glfwCreateWindow(640, 480, "Fractal Example", nullptr, nullptr);
  
  Fractal::Instance instance {{
    .logger_callback = LoggerFunc,
  }};

  Fractal::WindowSurface surface {{
    .instance = &instance,

#ifdef __APPLE__
    .window_handle = glfwGetCocoaView(window),
#endif
#ifdef WIN32
    .window_handle = glfwGetWin32Window(window),
#endif
  }};
  
  Fractal::RenderPass render_pass {{
    .surface = &surface,
  }};
  
  Fractal::Shader shader {{
    .instance = &instance,
    .surface = &surface,
    .vert_path = "build/shaders/example.vert.glsl.spv",
    .frag_path = "build/shaders/example.frag.glsl.spv",
  }};
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
}
