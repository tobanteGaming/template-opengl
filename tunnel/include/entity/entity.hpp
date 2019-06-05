#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "render/sprite.hpp"
#include "render/texture.hpp"

namespace tobanteGaming
{
// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(75, 75);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(650.0f);

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within Entity.
class Entity
{
public:
    // Constructor(s)
    Entity();
    Entity(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
           glm::vec3 color    = glm::vec3(1.0f),
           glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // Draw sprite
    virtual void Draw(SpriteRenderer& renderer);

public:
    // Object state
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    GLfloat Rotation;
    bool IsSolid;
    bool Destroyed;
    // Render state
    Texture2D Sprite;
};

}  // namespace tobanteGaming