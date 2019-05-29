project(template-opengl-example)

# GETTING STARTED
set(GETTING_STARTED ${PROJECT_NAME}_getting-started)
add_executable(${GETTING_STARTED} getting_started.cpp)
target_compile_features(${GETTING_STARTED} PUBLIC cxx_std_17)
target_compile_definitions(${GETTING_STARTED} PUBLIC GLEW_STATIC=1)
target_include_directories(${GETTING_STARTED} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${GETTING_STARTED} 
                    glfw 
                    ${GLFW_LIBRARIES} 
                    libglew_static
)