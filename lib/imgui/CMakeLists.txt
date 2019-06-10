project(imgui)

# Add library
add_library(${PROJECT_NAME} STATIC
        imconfig.h
        imgui.cpp
        imgui.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_impl_glfw_gl3.cpp
        imgui_impl_glfw_gl3.h
        imgui_internal.h
        stb_rect_pack.h
        stb_textedit.h
        stb_truetype.h
)

# Add alias
add_library(tobanteGaming::imgui ALIAS ${PROJECT_NAME})

# Include paths
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

# Link
target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        ${GLFW_LIBRARIES}
        libglew_static
)