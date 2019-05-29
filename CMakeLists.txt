cmake_minimum_required (VERSION 3.8)
project (template-opengl)

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
# set(GLM_TEST_ENABLE_CXX_17 ON CACHE STRING "" FORCE)
add_subdirectory(lib/glm)

# soil
add_subdirectory(lib/soil)

add_subdirectory(app)
add_subdirectory(examples)
