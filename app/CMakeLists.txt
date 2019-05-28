project(template-opengl-demo)

set(SOURCES
    src/application.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC=1)
target_link_libraries(${PROJECT_NAME} 
                    glfw 
                    ${GLFW_LIBRARIES} 
                    libglew_static
)