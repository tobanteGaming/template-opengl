#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "entity/entity.hpp"
#include "render/sprite_renderer.hpp"
#include "render/texture.hpp"

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(150.0f, -550.0f);
// Radius of the ball object
// const GLfloat BALL_RADIUS = 12.5f;
const GLfloat BALL_RADIUS = 25.0f;

// Ball holds the state of the Ball object inheriting
// relevant state data from Entity. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within Entity alone.
class Ball : public Entity
{
public:
    // Ball state
    GLfloat Radius;
    bool Stuck;
    // Constructor(s)
    Ball();
    Ball(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns
    // new position
    glm::vec2 Move(GLfloat dt, GLuint window_width);
    // Resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
};