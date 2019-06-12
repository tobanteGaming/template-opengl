cmake_minimum_required (VERSION 3.8)
project (template-opengl LANGUAGES CXX)

# Options
option(TOBANTEGAMING_TEMPLATE_OPENGL_EXAMPLES  "Build examples" ON)
option(TOBANTEGAMING_TEMPLATE_OPENGL_TESTS     "Build unit tests" ON)

# CMake setup
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerWarnings)
include(ConfigureOpenGL)

# Build static
set(BUILD_SHARED_LIBS OFF CACHE STRING "" FORCE)

# Include submodules
add_subdirectory(3rd_party/glfw)
add_subdirectory(3rd_party/glew)
add_subdirectory(3rd_party/glm)
add_subdirectory(3rd_party/imgui-cmake)
add_subdirectory(3rd_party/spdlog)

# Project
add_subdirectory(remisen_run)

# Examples
if(TOBANTEGAMING_TEMPLATE_OPENGL_EXAMPLES)
  add_subdirectory(examples)
endif()
