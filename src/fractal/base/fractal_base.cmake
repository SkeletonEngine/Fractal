set(FRACTAL_SRC_FRACTAL_FILES
  src/fractal/fractal.hpp
)
source_group("fractal" FILES ${FRACTAL_SRC_FRACTAL_FILES})

set(FRACTAL_SRC_FRACTAL_BASE_PLATFORM_FILES
  src/fractal/base/platform/window_handle.hpp
)
source_group("fractal/base/platform" FILES ${FRACTAL_SRC_FRACTAL_BASE_PLATFORM_FILES})

if (WIN32)
  set(FRACTAL_SRC_FRACTAL_BASE_PLATFORM_WINDOWS_FILES
    src/fractal/base/platform/windows/windows_forward_declarations.hpp
    src/fractal/base/platform/windows/windows_window_handle.cpp
  )
  source_group("fractal/base/platform/windows" FILES ${FRACTAL_SRC_FRACTAL_BASE_PLATFORM_WINDOWS_FILES})
endif()

if (APPLE)
  set(FRACTAL_SRC_FRACTAL_BASE_PLATFORM_MACOS_FILES
    src/fractal/base/platform/macos/macos_forward_declarations.hpp
    src/fractal/base/platform/macos/macos_window_handle.mm
  )
  source_group("fractal/base/platform/macos" FILES ${FRACTAL_SRC_FRACTAL_BASE_PLATFORM_MACOS_FILES})
endif()

set(FRACTAL_SRC_FRACTAL_BASE_COMMON_FILES
  src/fractal/base/common/assert.hpp
  src/fractal/base/common/base.hpp
  src/fractal/base/common/logger.hpp
  src/fractal/base/common/logger.cpp
  src/fractal/base/common/platform.hpp
)
source_group("fractal/base/common" FILES ${FRACTAL_SRC_FRACTAL_BASE_COMMON_FILES})

set(FRACTAL_SRC_FRACTAL_BASE_HELPERS_FILES
  src/fractal/base/helpers/spv_file.hpp
  src/fractal/base/helpers/spv_file.cpp
)
source_group("fractal/base/helpers" FILES ${FRACTAL_SRC_FRACTAL_BASE_HELPERS_FILES})

set(FRACTAL_SRC_FRACTAL_BASE_INSTANCE_FILES
  src/fractal/base/instance/instance_create_info.hpp
)
source_group("fractal/base/instance" FILES ${FRACTAL_SRC_FRACTAL_BASE_INSTANCE_FILES})

set(FRACTAL_SRC_FRACTAL_BASE_SURFACE_FILES
  src/fractal/base/surface/window_surface_create_info.hpp
)
source_group("fractal/base/surface" FILES ${FRACTAL_SRC_FRACTAL_BASE_SURFACE_FILES})

set(FRACTAL_SRC_FRACTAL_BASE_RENDER_PASS_FILES
  src/fractal/base/render_pass/render_pass_create_info.hpp
  src/fractal/base/render_pass/render_pass_begin_op.hpp
  src/fractal/base/render_pass/render_pass_end_op.hpp
)
source_group("fractal/base/render_pass" FILES ${FRACTAL_SRC_FRACTAL_BASE_RENDER_PASS_FILES})

set(FRACTAL_SRC_FRACTAL_BASE_SHADER_FILES
  src/fractal/base/shader/shader_create_info.hpp
)
source_group("fractal/base/shader" FILES ${FRACTAL_SRC_FRACTAL_BASE_SHADER_FILES})

set(FRACTAL_BASE_FILES
  ${FRACTAL_SRC_FRACTAL_FILES}

  ${FRACTAL_SRC_FRACTAL_BASE_PLATFORM_FILES}
  ${FRACTAL_SRC_FRACTAL_BASE_PLATFORM_WINDOWS_FILES}
  ${FRACTAL_SRC_FRACTAL_BASE_PLATFORM_MACOS_FILES}

  ${FRACTAL_SRC_FRACTAL_BASE_COMMON_FILES}
  ${FRACTAL_SRC_FRACTAL_BASE_HELPERS_FILES}
  ${FRACTAL_SRC_FRACTAL_BASE_INSTANCE_FILES}
  ${FRACTAL_SRC_FRACTAL_BASE_SURFACE_FILES}
  ${FRACTAL_SRC_FRACTAL_BASE_RENDER_PASS_FILES}
  ${FRACTAL_SRC_FRACTAL_BASE_SHADER_FILES}
)

if (NOT TARGET glm)
  add_subdirectory(src/lib/glm)
  set_target_properties(glm PROPERTIES FOLDER "Fractal/lib")
endif()