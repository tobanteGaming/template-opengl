#pragma once

#include <cstddef>
#include <string>

namespace rr
{
/**
 * @brief Default screen width.
 */
constexpr std::uint16_t DEFAULT_SCREEN_WIDTH = 1920;

/**
 * @brief Default screen height.
 */
constexpr std::uint16_t DEFAULT_SCREEN_HEIGHT = 1080;

/**
 * @brief Game name.
 */
constexpr char* GAME_NAME = "RemisenRun v0.1.0";

/**
 * @brief Path to resource folder (texture, shader & level).
 */
const std::string RESOURCE_PATH
    = R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\)";

}  // namespace rr