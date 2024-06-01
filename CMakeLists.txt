cmake_minimum_required(VERSION 3.27)
project(Fractal)

include(src/fractal/base/fractal_base.cmake)
include(src/fractal/backend/null/fractal_backend_null.cmake)
include(src/fractal/backend/vulkan/fractal_backend_vulkan.cmake)
