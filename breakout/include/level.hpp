#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "entity/entity.hpp"
#include "render/sprite_renderer.hpp"
#include "resource_manager.hpp"

/// Level holds all Tiles as part of a Breakout level and
/// hosts functionality to Load/render levels from the harddisk.
class Level
{
public:
    // Level state
    std::vector<Entity> Bricks;
    // Constructor
    Level() = default;
    // Loads level from file
    void Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight);
    // Render level
    void Draw(SpriteRenderer& renderer);
    // Check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();

private:
    // Initialize level from tile data
    void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth,
              GLuint levelHeight);
};