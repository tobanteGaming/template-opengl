project(imgui-neo)

# Add library
add_library(${PROJECT_NAME} STATIC
        imgui/imconfig.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_widgets.cpp

        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h

        imgui/examples/imgui_impl_glfw.cpp
        imgui/examples/imgui_impl_glfw.h
        imgui/examples/imgui_impl_opengl3.cpp
        imgui/examples/imgui_impl_opengl3.h
)

# Add alias
add_library(tobanteGaming::imgui ALIAS ${PROJECT_NAME})

# Settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/imgui/examples)
target_compile_definitions(${PROJECT_NAME} PUBLIC
        GLEW_STATIC=1
        IMGUI_IMPL_OPENGL_LOADER_GLEW=1
)

# Link
target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        ${GLFW_LIBRARIES}
        libglew_static
        tobanteGaming::CompilerWarnings
        tobanteGaming::CompilerOptions
)
