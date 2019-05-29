#pragma once

#include <string>


struct GLFWwindow;

namespace tobanteGaming
{
class Window
{
public:
  int Init(std::string name);
  void Destroy();
  GLFWwindow* getRawWindow() { return m_window; }

private:
  GLFWwindow* m_window;
};
} // namespace tobanteGaming