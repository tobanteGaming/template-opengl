#pragma once

#include "core/common.hpp"
#include "render/shader.hpp"
#include "render/window.hpp"
#include "shape/cube.hpp"

namespace tobanteGaming
{
class Application
{
public:
    Application(String name);
    ~Application();
    void Init();
    void Run();

private:
    // Init
    void openGLInit();
    void imguiInit();
    void registerCallbacks();

    void drawImgui();

private:
    String m_name;
    Pointer<Window> m_window;

    Pointer<Shader> m_shader;
    Pointer<Cube> m_cube;

    ImVec4 clear_color = ImColor(114, 144, 154);
};

}  // namespace tobanteGaming