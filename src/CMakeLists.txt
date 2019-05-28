project(template-opengl-demo)

set(SOURCES 
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} libglew_static)