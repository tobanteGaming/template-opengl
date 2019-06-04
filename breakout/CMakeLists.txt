project(breakout)

set(PROJECT_LIBRARY ${PROJECT_NAME}-lib)
set(LIB_SOURCES
    src/collision.cpp
    src/entity/ball.cpp
    src/entity/entity.cpp
    src/game.cpp
    src/level.cpp
    src/render/particle_generator.cpp
    src/render/sprite_renderer.cpp
    src/render/shader.cpp
    src/render/texture.cpp
    src/resource_manager.cpp
)

add_library(${PROJECT_LIBRARY} STATIC ${LIB_SOURCES} )
add_library(tobanteGaming::Application ALIAS ${PROJECT_LIBRARY})

target_include_directories( ${PROJECT_LIBRARY} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_LIBRARY} PUBLIC GLEW_STATIC=1)
target_compile_features(${PROJECT_LIBRARY} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_LIBRARY} PRIVATE
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
                    tobanteGaming::Application
                    tobanteGaming::CompilerWarnings
                    glfw
                    ${GLFW_LIBRARIES}
                    libglew_static
                    glm
)