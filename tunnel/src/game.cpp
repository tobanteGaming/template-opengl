#include <iostream>

#include "game.hpp"

#include "resource_manager.hpp"

std::array<bool, 1024> Game::Keys{};

Game::Game(GLuint width, GLuint height)
    : m_state(GAME_ACTIVE), m_width(width), m_height(height)
{
}

void Game::Init()
{
    using RM = ResourceManager;

    // Load shaders
    RM::LoadShader(R"(shaders\sprite_vs.glsl)", R"(shaders\sprite_fs.glsl)",
                   nullptr, "sprite");
    RM::LoadShader(R"(shaders\particle_vs.glsl)", R"(shaders\particle_fs.glsl)",
                   nullptr, "particle");

    // Configure shaders
    const auto f_width  = static_cast<float>(m_width);
    const auto f_height = static_cast<float>(m_height);
    auto projection = glm::ortho(0.0f, f_width, f_height, 0.0f, -1.0f, 1.0f);
    RM::GetShader("sprite").Use().SetInteger("sprite", 0);
    RM::GetShader("sprite").SetMatrix4("projection", projection);
    RM::GetShader("particle").Use().SetInteger("sprite", 0);
    RM::GetShader("particle").SetMatrix4("projection", projection);

    // Load textures
    RM::LoadTexture(R"(texture\background.jpg)", GL_FALSE, "background");
    RM::LoadTexture(R"(texture\awesomeface.png)", GL_TRUE, "face");
    RM::LoadTexture(R"(texture\smiley.png)", GL_TRUE, "smiley");
    RM::LoadTexture(R"(texture\smiley2.png)", GL_TRUE, "smiley2");
    RM::LoadTexture(R"(texture\block.png)", GL_TRUE, "block");
    RM::LoadTexture(R"(texture\block_solid.png)", GL_TRUE, "block_solid");
    RM::LoadTexture(R"(texture\paddle.png)", GL_TRUE, "paddle");
    RM::LoadTexture(R"(texture\particle.png)", GL_TRUE, "particle");

    // Set render-specific controls
    m_renderer.reset(new SpriteRenderer(RM::GetShader("sprite")));
    m_particles.reset(new ParticleGenerator(RM::GetShader("particle"),
                                            RM::GetTexture("particle"), 500));

    // Configure game objects
    const auto playerPos
        = glm::vec2(m_width / 2 - PLAYER_SIZE.x / 2, m_height - PLAYER_SIZE.y);
    m_player.reset(
        new Entity(playerPos, PLAYER_SIZE, RM::GetTexture("smiley2")));
}

void Game::Update(GLfloat dt)
{
    // Update objects
    // m_ball->Move(dt, m_width);

    // Update particles
    m_particles->Update(dt, *m_player, 2, glm::vec2(100 / 2));

    // Check loss condition
    // Check for collisions
    // DoCollisions();
}

void Game::ProcessInput(GLfloat dt)
{
    if (m_state == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;

        // Move playerboard
        if (Keys[GLFW_KEY_A] || Keys[GLFW_KEY_LEFT])
        {
            if (m_player->Position.x >= 0)
            {
                m_player->Position.x -= velocity;
            }
        }
        if (Keys[GLFW_KEY_D] || Keys[GLFW_KEY_RIGHT])
        {
            if (m_player->Position.x <= m_width - m_player->Size.x)
            {
                m_player->Position.x += velocity;
            }
        }
        if (Keys[GLFW_KEY_ENTER])
        {
            ResetPlayer();
        }
        // if (Keys[GLFW_KEY_SPACE]) { m_ball->Stuck = false; }
    }
}

void Game::Render()
{
    if (m_state == GAME_ACTIVE)
    {
        // Draw background
        auto bg_texture = ResourceManager::GetTexture("background");
        m_renderer->DrawSprite(bg_texture, glm::vec2(0, 0),
                               glm::vec2(m_width, m_height), 0.0f);
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        glUseProgram(NULL);
        glLoadIdentity();  // load identity matrix

        // glTranslatef(0.0f, 0.0f, -4.0f);  // move forward 4 units
        glColor3f(0.0f, 1.0f, 1.0f);  // blue color

        glLineWidth(10.0f);
        glBegin(GL_LINES);  // starts drawing of points
        glVertex3f(-0.6f, 1.0f, 0.0f);
        glVertex3f(-0.5f, -1.0f, 0.0f);

        glVertex3f(0.6f, 1.0f, 0.0f);
        glVertex3f(0.5f, -1.0f, 0.0f);
        glEnd();  // end drawing of points

        // Draw player
        m_player->Draw(*m_renderer);

        // Draw particles
        m_particles->Draw();
    }
}

void Game::ResetLevel() {}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    m_player->Size = PLAYER_SIZE;
    m_player->Position
        = glm::vec2(m_width / 2 - PLAYER_SIZE.x / 2, m_height - PLAYER_SIZE.y);
}

void Game::DoCollisions() {}
