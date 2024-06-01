set(FRACTAL_SRC_EXAMPLE_FILES
  src/example/main.cpp
)
source_group("src" FILES ${FRACTAL_SRC_EXAMPLE_FILES})

add_executable("FractalBackend${FRACTAL_BACKEND_NAME}Example" 
  ${FRACTAL_SRC_EXAMPLE_FILES}
  ${FRACTAL_SRC_EXAMPLE_PLATFORM_MACOS_FILES}
  ${FRACTAL_SRC_EXAMPLE_PLATFORM_WINDOWS_FILES}
)
target_compile_features("FractalBackend${FRACTAL_BACKEND_NAME}Example" PUBLIC cxx_std_20)
target_include_directories("FractalBackend${FRACTAL_BACKEND_NAME}Example" PUBLIC src)
target_link_libraries("FractalBackend${FRACTAL_BACKEND_NAME}Example" PRIVATE "FractalBackend${FRACTAL_BACKEND_NAME}")
set_target_properties("FractalBackend${FRACTAL_BACKEND_NAME}Example" PROPERTIES FOLDER "Fractal/Examples")

if (APPLE)
  target_link_libraries("FractalBackend${FRACTAL_BACKEND_NAME}Example" PRIVATE "-framework Cocoa")
endif()

if (NOT TARGET glfw)
  add_subdirectory(src/lib/glfw)
  set_target_properties(glfw PROPERTIES FOLDER "Fractal/lib/GLFW3")
  set_target_properties(uninstall PROPERTIES FOLDER "Fractal/lib/GLFW3")
  set_target_properties(update_mappings PROPERTIES FOLDER "Fractal/lib/GLFW3")
endif()
target_link_libraries("FractalBackend${FRACTAL_BACKEND_NAME}Example" PRIVATE glfw)
