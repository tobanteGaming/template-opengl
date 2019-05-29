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

# SHADER_CLASS
set(SHADER_CLASS ${PROJECT_NAME}_shader-class)
add_executable(${SHADER_CLASS} shader_class.cpp)
target_compile_features(${SHADER_CLASS} PUBLIC cxx_std_17)
target_compile_definitions(${SHADER_CLASS} PUBLIC GLEW_STATIC=1)
target_include_directories(${SHADER_CLASS} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${SHADER_CLASS} 
                    glfw 
                    ${GLFW_LIBRARIES} 
                    libglew_static
)

# TEXTURES
set(TEXTURES ${PROJECT_NAME}_textures)
add_executable(${TEXTURES} textures.cpp stb_image.cpp)
target_compile_features(${TEXTURES} PUBLIC cxx_std_17)
target_compile_definitions(${TEXTURES} PUBLIC GLEW_STATIC=1)
target_include_directories(${TEXTURES} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${TEXTURES} 
                    glfw 
                    ${GLFW_LIBRARIES} 
                    libglew_static
)