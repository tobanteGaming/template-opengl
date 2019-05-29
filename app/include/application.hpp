#pragma once

#include <string>

#include "window.hpp"

namespace tobanteGaming
{
class Application
{
public:
  Application(std::string name);

  int Run();

private:
  std::string m_name;
  tobanteGaming::Window m_window;
};
} // namespace tobanteGaming