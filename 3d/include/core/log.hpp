#pragma once

#include "spdlog/spdlog.h"

#include "spdlog/fmt/ostr.h"

namespace tobanteGaming
{
class Log
{
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
    {
        return s_Logger;
    }

private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

}  // namespace tobanteGaming

// Core log macros
#define LOG_TRACE(...) ::tobanteGaming::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::tobanteGaming::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::tobanteGaming::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::tobanteGaming::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)                                                         \
    ::tobanteGaming::Log::GetCoreLogger()->critical(__VA_ARGS__)
