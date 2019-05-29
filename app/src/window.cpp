#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

namespace tobanteGaming
{
int Window::Init(std::string name)
{
    auto error_callback
        = [](int error, const char* description) { std::cout << "Error: " << description << '\n'; };
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) { exit(EXIT_FAILURE); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    m_window = glfwCreateWindow(1280, 720, name.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        std::cout << "Error creating GLFW window" << '\n';
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(m_window);

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

    // GLEW
    if (glewInit() != GLEW_OK) { std::cout << "Error in glew init" << '\n'; }
    std::cout << glGetString(GL_VERSION) << '\n';

    return EXIT_SUCCESS;
}

void Window::Destroy() { glfwDestroyWindow(m_window); }
}  // namespace tobanteGaming