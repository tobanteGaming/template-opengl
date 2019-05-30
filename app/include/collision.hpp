#pragma once

#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "entity/ball_object.hpp"
#include "entity/game_object.hpp"

// Represents the four possible (collision) directions
enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// Defines a Collision typedef that represents collision data
// <collision?, what direction?, difference vector center - closest point>
using Collision = std::tuple<bool, Direction, glm::vec2>;

bool CheckCollision(Entity& one, Entity& two);
Collision CheckCollision(Ball& one, Entity& two);

// Calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target);