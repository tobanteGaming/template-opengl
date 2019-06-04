#include "render/particle_generator.hpp"

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, GLuint amount)
    : m_shader(shader), m_texture(texture), m_amount(amount)
{
    init();
}

void ParticleGenerator::Update(GLfloat dt, Entity& object, GLuint newParticles, glm::vec2 offset)
{
    // Add new particles
    for (GLuint i = 0; i < newParticles; ++i)
    {
        int unusedParticle = firstUnusedParticle();
        respawnParticle(m_particles[unusedParticle], object, offset);
    }
    // Update all particles
    for (GLuint i = 0; i < m_amount; ++i)
    {
        Particle& p = m_particles[i];
        p.Life -= dt;  // reduce life
        if (p.Life > 0.0f)
        {  // particle is alive, thus update
            p.Position -= p.Velocity * dt;
            p.Color.a -= dt * 2.5f;
        }
    }
}

// Render all particles
void ParticleGenerator::Draw()
{
    // Use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    m_shader.Use();
    for (Particle particle : m_particles)
    {
        if (particle.Life > 0.0f)
        {
            m_shader.SetVector2f("offset", particle.Position);
            m_shader.SetVector4f("color", particle.Color);
            m_texture.Bind();
            glBindVertexArray(m_vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // Don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
    // Set up mesh and attribute properties
    GLuint VBO;
    GLfloat particle_quad[]
        = {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

           0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &VBO);
    glBindVertexArray(m_vao);
    // Fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    // Create amount default particle instances
    for (GLuint i = 0; i < m_amount; ++i) m_particles.push_back(Particle());
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
GLuint ParticleGenerator::firstUnusedParticle()
{
    // First search from last used particle, this will usually return almost instantly
    for (GLuint i = lastUsedParticle; i < m_amount; ++i)
    {
        if (m_particles[i].Life <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }
    // Otherwise, do a linear search
    for (GLuint i = 0; i < lastUsedParticle; ++i)
    {
        if (m_particles[i].Life <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }
    // All particles are taken, override the first one (note that if it repeatedly hits this case,
    // more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle& particle, Entity& object, glm::vec2 offset)
{
    GLfloat random    = ((rand() % 100) - 50) / 10.0f;
    GLfloat rColor    = 0.5f + ((rand() % 100) / 100.0f);
    particle.Position = object.Position + random + offset;
    particle.Color    = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.Life     = 1.0f;
    particle.Velocity = object.Velocity * 0.1f;
}