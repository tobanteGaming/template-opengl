#pragma once

#include <string>

namespace tobanteGaming
{
class Application
{
public:
    Application(std::string name);

    int Run();

private:
    std::string m_name;
};
} // namespace tobanteGaming