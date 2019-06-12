project(3d-tutorial)

set(SOURCES
    main.cpp

    src/controls.cpp
    src/objloader.cpp
    src/quaternion_utils.cpp
    src/tangentspace.cpp
    src/text2D.cpp
    src/shader.cpp
    src/texture.cpp
    src/vboindexer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC=1)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/common)
target_link_libraries(${PROJECT_NAME}
                    glfw
                    ${GLFW_LIBRARIES}
                    libglew_static
                    glm
                    tobanteGaming::Soil
                    tobanteGaming::CompilerWarnings
                    tobanteGaming::CompilerWarnings
)