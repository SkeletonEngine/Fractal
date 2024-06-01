set(FRACTAL_SRC_EXAMPLE_FILES
  src/example/main.cpp
)
source_group("src" FILES ${FRACTAL_SRC_EXAMPLE_FILES})

set(FRACTAL_SRC_EXAMPLE_SHADER_FILES
  src/example/shaders/example.frag.glsl
  src/example/shaders/example.vert.glsl
)
source_group("src/shaders" FILES ${FRACTAL_SRC_EXAMPLE_SHADER_FILES})

add_executable("FractalBackend${FRACTAL_BACKEND_NAME}Example" 
  ${FRACTAL_SRC_EXAMPLE_FILES}
  ${FRACTAL_SRC_EXAMPLE_SHADER_FILES}
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

include(src/fractal/base/shader_compile_helper.cmake)
create_shader_compile_target("FractalBackend${FRACTAL_BACKEND_NAME}ExampleShaders" "${CMAKE_CURRENT_BINARY_DIR}/../aliens/"
  src/example/shaders/example.vert.glsl
  src/example/shaders/example.frag.glsl
)
add_dependencies("FractalBackend${FRACTAL_BACKEND_NAME}Example" "FractalBackend${FRACTAL_BACKEND_NAME}ExampleShaders")
set_target_properties("FractalBackend${FRACTAL_BACKEND_NAME}ExampleShaders" PROPERTIES FOLDER "Fractal/Examples")

if(APPLE)
  set_target_properties("FractalBackend${FRACTAL_BACKEND_NAME}Example" PROPERTIES XCODE_GENERATE_SCHEME TRUE XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
if(WIN32)
  set_target_properties("FractalBackend${FRACTAL_BACKEND_NAME}Example" PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
