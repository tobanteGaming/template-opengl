project(3d)

set(PROJECT_LIBRARY ${PROJECT_NAME}-lib)
set(LIB_SOURCES
    src/shader.cpp
)

add_library(${PROJECT_LIBRARY} STATIC ${LIB_SOURCES} )
add_library(tobanteGaming::3D ALIAS ${PROJECT_LIBRARY})

target_include_directories( ${PROJECT_LIBRARY} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_LIBRARY} PUBLIC GLEW_STATIC=1)
target_compile_features(${PROJECT_LIBRARY} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_LIBRARY} PUBLIC
                    glfw
                    ${GLFW_LIBRARIES}
                    libglew_static
                    glm
                    tobanteGaming::Soil
                    tobanteGaming::CompilerWarnings
)


set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}
                    tobanteGaming::3D
                    tobanteGaming::CompilerWarnings
)