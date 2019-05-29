#pragma once

#include <string>

namespace rr
{
/**
 * @brief Default screen width.
 */
constexpr unsigned int DEFAULT_SCREEN_WIDTH = 1280;

/**
 * @brief Default screen height.
 */
constexpr unsigned int DEFAULT_SCREEN_HEIGHT = 720;

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