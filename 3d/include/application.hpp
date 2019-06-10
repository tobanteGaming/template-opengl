#pragma once

#include "core/common.hpp"
#include "shader.hpp"
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
    String m_name;
    GLFWwindow* m_window;

    Pointer<Shader> ourShader;
    Pointer<Cube> cube;

    bool show_test_window    = true;
    bool show_another_window = false;
    ImVec4 clear_color       = ImColor(114, 144, 154);
};

}  // namespace tobanteGaming