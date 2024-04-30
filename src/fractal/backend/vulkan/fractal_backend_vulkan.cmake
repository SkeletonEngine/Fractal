if (WIN32)
  set(FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_PLATFORM_WINDOWS_FILES
    src/fractal/backend/vulkan/platform/windows/vulkan_platform_windows_create_window_surface.cpp
  )
  source_group("fractal/backend/vulkan/platform/windows" FILES ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_PLATFORM_WINDOWS_FILES})
endif()

if (APPLE)
  set(FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_PLATFORM_MACOS_FILES
    src/fractal/backend/vulkan/platform/macos/vulkan_platform_macos_create_window_surface.mm
  )
  source_group("fractal/backend/vulkan/platform/macos" FILES ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_PLATFORM_MACOS_FILES})
endif()

set(FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_COMMON_FILES
  src/fractal/backend/vulkan/common/vulkan_assert.hpp
  src/fractal/backend/vulkan/common/vulkan_base.hpp
  src/fractal/backend/vulkan/common/vulkan_forward_declarations.hpp
)
source_group("fractal/backend/vulkan/common" FILES ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_COMMON_FILES})

set(FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_INSTANCE_FILES
  src/fractal/backend/vulkan/instance/vulkan_instance.cpp
  src/fractal/backend/vulkan/instance/vulkan_instance_data.hpp
  src/fractal/backend/vulkan/instance/vulkan_instance_extensions.hpp
  src/fractal/backend/vulkan/instance/vulkan_instance_extensions.cpp
  src/fractal/backend/vulkan/instance/vulkan_validation_layers.hpp
  src/fractal/backend/vulkan/instance/vulkan_validation_layers.cpp
  src/fractal/backend/vulkan/instance/vulkan_queue_family_indices.hpp
  src/fractal/backend/vulkan/instance/vulkan_queue_family_indices.cpp
  src/fractal/backend/vulkan/instance/vulkan_device.hpp
  src/fractal/backend/vulkan/instance/vulkan_device.cpp
)
source_group("fractal/backend/vulkan/instance" FILES ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_INSTANCE_FILES})

set(FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_SURFACE_FILES
  src/fractal/backend/vulkan/surface/vulkan_window_surface.cpp
  src/fractal/backend/vulkan/surface/vulkan_window_surface_data.hpp
  src/fractal/backend/vulkan/surface/vulkan_platform_create_window_surface.hpp
)
source_group("fractal/backend/vulkan/surface" FILES ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_SURFACE_FILES})

set(FRACTAL_BACKEND_VULKAN_FILES
  ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_PLATFORM_WINDOWS_FILES}
  ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_PLATFORM_MACOS_FILES}

  ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_COMMON_FILES}
  ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_INSTANCE_FILES}
  ${FRACTAL_SRC_FRACTAL_BACKEND_VULKAN_SURFACE_FILES}
)

add_library(FractalBackendVulkan
  ${FRACTAL_BASE_FILES}
  ${FRACTAL_BACKEND_VULKAN_FILES}
)
target_compile_features(FractalBackendVulkan PUBLIC cxx_std_20)
target_include_directories(FractalBackendVulkan PUBLIC src)
set_target_properties(FractalBackendVulkan PROPERTIES FOLDER "Fractal/Vulkan")

if (APPLE)
  target_link_libraries(FractalBackendVulkan PRIVATE "-framework Cocoa")
endif()

if(WIN32)
  set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
endif()
add_subdirectory(src/lib/volk)
set_target_properties(volk PROPERTIES FOLDER "Fractal/Vulkan")
target_link_libraries(FractalBackendVulkan PRIVATE volk)

if (PROJECT_IS_TOP_LEVEL)
  set(FRACTAL_BACKEND_NAME Vulkan)
  include(src/fractal/fractal_example.cmake)
endif()
