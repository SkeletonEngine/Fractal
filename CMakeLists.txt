cmake_minimum_required(VERSION 3.27)
project(Fractal)

add_subdirectory(src/lib/glm)

include(src/fractal/fractal_base.cmake)
include(src/fractal/backend/null/fractal_backend_null.cmake)
include(src/fractal/backend/vulkan/fractal_backend_vulkan.cmake)
