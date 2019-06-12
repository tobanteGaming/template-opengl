#pragma once

#include <array>
#include <memory>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"

namespace tobanteGaming
{
class Application
{
public:
    Application(std::string name);
    ~Application();

    void Init();
    void Run();

private:
    std::string m_name;
    GLFWwindow* m_window;

    std::unique_ptr<Game> Breakout;
};
}  // namespace tobanteGaming