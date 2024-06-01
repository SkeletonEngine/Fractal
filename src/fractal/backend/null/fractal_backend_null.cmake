set(FRACTAL_SRC_FRACTAL_BACKEND_NULL_INSTANCE_FILES
  src/fractal/backend/null/instance/null_instance.hpp
  src/fractal/backend/null/instance/null_instance.cpp
)
source_group("fractal/backend/null/instance" FILES ${FRACTAL_SRC_FRACTAL_BACKEND_NULL_INSTANCE_FILES})

set(FRACTAL_SRC_FRACTAL_BACKEND_NULL_SURFACE_FILES
  src/fractal/backend/null/surface/null_window_surface.hpp
  src/fractal/backend/null/surface/null_window_surface.cpp
)
source_group("fractal/backend/null/surface" FILES ${FRACTAL_SRC_FRACTAL_BACKEND_NULL_SURFACE_FILES})

set(FRACTAL_BACKEND_NULL_FILES
  ${FRACTAL_SRC_FRACTAL_BACKEND_NULL_INSTANCE_FILES}
  ${FRACTAL_SRC_FRACTAL_BACKEND_NULL_SURFACE_FILES}
)

add_library(FractalBackendNull
  ${FRACTAL_BASE_FILES}
  ${FRACTAL_BACKEND_NULL_FILES}
)
target_compile_features(FractalBackendNull PUBLIC cxx_std_20)
target_include_directories(FractalBackendNull PUBLIC src)
set_target_properties(FractalBackendNull PROPERTIES FOLDER "Fractal")
target_compile_definitions(FractalBackendNull PUBLIC FRACTAL_BACKEND_NULL)

if (PROJECT_IS_TOP_LEVEL)
  set(FRACTAL_BACKEND_NAME Null)
  include(src/example/fractal_example.cmake)
endif()
