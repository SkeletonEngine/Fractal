set(FRACTAL_SRC_EXAMPLE_FILES
  src/example/main.cpp
)
source_group("src" FILES ${FRACTAL_SRC_EXAMPLE_FILES})

if (APPLE)
  set(FRACTAL_SRC_EXAMPLE_PLATFORM_MACOS_FILES
    src/example/platform/macos/macos_window.hpp
    src/example/platform/macos/macos_window.mm
  )
  source_group("src/platform/macos" FILES ${FRACTAL_SRC_EXAMPLE_PLATFORM_MACOS_FILES})
endif()

add_executable("FractalBackend${FRACTAL_BACKEND_NAME}Example" 
  ${FRACTAL_SRC_EXAMPLE_FILES}
  ${FRACTAL_SRC_EXAMPLE_PLATFORM_MACOS_FILES}
)
target_compile_features("FractalBackend${FRACTAL_BACKEND_NAME}Example" PUBLIC cxx_std_20)
target_include_directories("FractalBackend${FRACTAL_BACKEND_NAME}Example" PUBLIC src)
target_link_libraries("FractalBackend${FRACTAL_BACKEND_NAME}Example" PRIVATE "FractalBackend${FRACTAL_BACKEND_NAME}")
set_target_properties("FractalBackend${FRACTAL_BACKEND_NAME}Example" PROPERTIES FOLDER "Fractal/Examples")
