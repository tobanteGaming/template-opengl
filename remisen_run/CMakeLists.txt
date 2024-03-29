project(remisen-run)

set(PROJECT_LIBRARY ${PROJECT_NAME}-lib)
set(LIB_SOURCES
    src/application.cpp
    src/core/log.cpp
    src/render/shader.cpp
    src/render/window.cpp
)

add_library(${PROJECT_LIBRARY} STATIC ${LIB_SOURCES} )
add_library(tobanteGaming::RemisenRun ALIAS ${PROJECT_LIBRARY})

target_include_directories( ${PROJECT_LIBRARY} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_LIBRARY} PUBLIC GLEW_STATIC=1)
target_compile_features(${PROJECT_LIBRARY} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_LIBRARY} PUBLIC
                    glfw
                    ${GLFW_LIBRARIES}
                    libglew_static
                    glm
                    spdlog::spdlog
                    tobanteGaming::CompilerWarnings
                    tobanteGaming::CompilerOptions
                    tobanteGaming::imgui
)


set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}
                    tobanteGaming::RemisenRun
                    tobanteGaming::CompilerWarnings
                    tobanteGaming::CompilerOptions
)