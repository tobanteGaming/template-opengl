cmake_minimum_required (VERSION 3.8)
project (template-opengl LANGUAGES CXX)

# Options
option(TOBANTEGAMING_OPENGL_BUILD_EXAMPLES  "Build examples" ON)
option(TOBANTEGAMING_OPENGL_BUILD_TESTS     "Build unit tests" ON)
option(TOBANTEGAMING_OPENGL_ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

# Cmake setup
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerWarnings)


set(BUILD_SHARED_LIBS OFF CACHE STRING "" FORCE)

# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE STRING "" FORCE)
set(GLFW_INSTALL        OFF CACHE STRING "" FORCE)
add_subdirectory(lib/glfw)

# glew
set(glew-cmake_BUILD_SHARED OFF CACHE STRING "" FORCE)
add_subdirectory(lib/glew)

# glm
set(GLM_TEST_ENABLE OFF CACHE STRING "" FORCE)
add_subdirectory(lib/glm)

# soil
add_subdirectory(lib/soil)

add_subdirectory(tunnel)
# add_subdirectory(breakout)
add_subdirectory(examples)
