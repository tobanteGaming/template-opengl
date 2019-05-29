#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "entity/game_object.hpp"

GLboolean CheckCollision(GameObject& one, GameObject& two)
{
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x
                      && two.Position.x + two.Size.x >= one.Position.x;

    bool collisionY = one.Position.y + one.Size.y >= two.Position.y
                      && two.Position.y + two.Size.y >= one.Position.y;

    return collisionX && collisionY;
}