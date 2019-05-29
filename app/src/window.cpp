#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace tobanteGaming
{
int Window::Init(std::string name)
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  m_window = glfwCreateWindow(1280, 720, name.c_str(), nullptr, nullptr);
  if (!m_window)
  {
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(m_window);


  glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode,
                                  int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
  });
}

void Window::Destroy() { glfwDestroyWindow(m_window); }
} // namespace tobanteGaming
