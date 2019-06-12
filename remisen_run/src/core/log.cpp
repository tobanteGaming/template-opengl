#include "core/log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace tobanteGaming
{
std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init()
{
    s_Logger = spdlog::stdout_color_mt("RemisenRun");
    s_Logger->set_level(spdlog::level::trace);
}

}  // namespace tobanteGaming