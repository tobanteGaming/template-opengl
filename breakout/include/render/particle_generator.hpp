#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "entity/entity.hpp"
#include "render/shader.hpp"
#include "render/texture.hpp"

// Represents a single particle and its state
struct Particle
{
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    GLfloat Life{0.0f};

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f) {}
};

// ParticleGenerator acts as a container for rendering a large number of
// particles by repeatedly spawning and updating particles and killing
// them after a given amount of time.
class ParticleGenerator
{
public:
    // Constructor
    ParticleGenerator(Shader shader, Texture2D texture, GLuint amount);
    // Update all particles
    void Update(GLfloat dt, Entity& object, GLuint newParticles,
                glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    // Render all particles
    void Draw();

private:
    // Initializes buffer and vertex attributes
    void init();
    // Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle
    // is currently inactive
    GLuint firstUnusedParticle();
    // Respawns particle
    void respawnParticle(Particle& particle, Entity& object,
                         glm::vec2 offset = glm::vec2(0.0f, 0.0f));

private:
    // State
    std::vector<Particle> m_particles;
    GLuint m_amount;
    // Render state
    Shader m_shader;
    Texture2D m_texture;
    GLuint m_vao;
};
