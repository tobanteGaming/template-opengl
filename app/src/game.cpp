#include <iostream>

#include "game.hpp"

#include "resource_manager.hpp"

Game::Game(GLuint width, GLuint height) : m_state(GAME_ACTIVE), Keys(), m_width(width), m_height(height) {}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader(R"(shaders\sprite_vs.glsl)", R"(shaders\sprite_fs.glsl)", nullptr,
                                "sprite");
    ResourceManager::LoadShader(R"(shaders\particle_vs.glsl)", R"(shaders\particle_fs.glsl)", nullptr,
                                "particle");
    // Configure shaders
    const auto f_width  = static_cast<float>(m_width);
    const auto f_height = static_cast<float>(m_height);
    auto projection     = glm::ortho(0.0f, f_width, f_height, 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("particle").SetMatrix4("projection", projection);

    // Load textures
    ResourceManager::LoadTexture(R"(texture\background.jpg)", GL_FALSE, "background");
    ResourceManager::LoadTexture(R"(texture\awesomeface.png)", GL_TRUE, "face");
    ResourceManager::LoadTexture(R"(texture\block.png)", GL_FALSE, "block");
    ResourceManager::LoadTexture(R"(texture\block_solid.png)", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture(R"(texture\paddle.png)", true, "paddle");
    ResourceManager::LoadTexture(R"(texture\particle.png)", true, "particle");

    // Set render-specific controls
    m_renderer  = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    m_particles = std::make_unique<ParticleGenerator>(ResourceManager::GetShader("particle"),
                                                    ResourceManager::GetTexture("particle"), 500);
    // Load levels
    GameLevel one;
    GameLevel two;
    GameLevel three;
    GameLevel four;
    one.Load(R"(levels\001.lvl)", m_width, m_height * 0.5);
    two.Load(R"(levels\002.lvl)", m_width, m_height * 0.5);
    three.Load(R"(levels\003.lvl)", m_width, m_height * 0.5);
    four.Load(R"(levels\004.lvl)", m_width, m_height * 0.5);
    m_levels.push_back(one);
    m_levels.push_back(two);
    m_levels.push_back(three);
    m_levels.push_back(four);

    m_current_level = 0;

    // Configure game objects
    glm::vec2 playerPos = glm::vec2(m_width / 2 - PLAYER_SIZE.x / 2, m_height - PLAYER_SIZE.y);
    m_player
        = std::make_unique<GameObject>(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    // m_ball
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    m_ball              = std::make_unique<BallObject>(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                                        ResourceManager::GetTexture("face"));
}

void Game::Update(GLfloat dt)
{
    // Update objects
    m_ball->Move(dt, this->m_width);
    // Check for collisions
    this->DoCollisions();
    // Update particles
    m_particles->Update(dt, *m_ball, 2, glm::vec2(m_ball->Radius / 2));
    // Check loss condition
    if (m_ball->Position.y >= this->m_height)  // Did ball reach bottom edge?
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
}

void Game::ProcessInput(GLfloat dt)
{
    if (this->m_state == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (m_player->Position.x >= 0)
            {
                m_player->Position.x -= velocity;
                if (m_ball->Stuck) m_ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (m_player->Position.x <= this->m_width - m_player->Size.x)
            {
                m_player->Position.x += velocity;
                if (m_ball->Stuck) m_ball->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE]) m_ball->Stuck = false;
    }
}

void Game::Render()
{
    if (this->m_state == GAME_ACTIVE)
    {
        // Draw background
        m_renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0),
                             glm::vec2(this->m_width, this->m_height), 0.0f);
        // Draw level
        this->m_levels[this->m_current_level].Draw(*m_renderer);
        // Draw player
        m_player->Draw(*m_renderer);
        // Draw particles
        m_particles->Draw();
        // Draw ball
        m_ball->Draw(*m_renderer);
    }
}

void Game::ResetLevel()
{
    if (this->m_current_level == 0)
        this->m_levels[0].Load("levels/001.lvl", this->m_width, this->m_height * 0.5f);
    else if (this->m_current_level == 1)
        this->m_levels[1].Load("levels/002.lvl", this->m_width, this->m_height * 0.5f);
    else if (this->m_current_level == 2)
        this->m_levels[2].Load("levels/003.lvl", this->m_width, this->m_height * 0.5f);
    else if (this->m_current_level == 3)
        this->m_levels[3].Load("levels/004.lvl", this->m_width, this->m_height * 0.5f);
}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    m_player->Size     = PLAYER_SIZE;
    m_player->Position = glm::vec2(this->m_width / 2 - PLAYER_SIZE.x / 2, this->m_height - PLAYER_SIZE.y);
    m_ball->Reset(m_player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)),
                INITIAL_BALL_VELOCITY);
}

void Game::DoCollisions()
{
    for (GameObject& box : this->m_levels[this->m_current_level].Bricks)
    {
        if (!box.Destroyed)
        {
            Collision collision = CheckCollision(*m_ball, box);
            if (std::get<0>(collision))  // If collision is true
            {
                // Destroy block if not solid
                if (!box.IsSolid) box.Destroyed = GL_TRUE;
                // Collision resolution
                Direction dir         = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT)  // Horizontal collision
                {
                    m_ball->Velocity.x = -m_ball->Velocity.x;  // Reverse horizontal velocity
                    // Relocate
                    GLfloat penetration = m_ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        m_ball->Position.x += penetration;  // Move ball to right
                    else
                        m_ball->Position.x -= penetration;  // Move ball to left;
                }
                else  // Vertical collision
                {
                    m_ball->Velocity.y = -m_ball->Velocity.y;  // Reverse vertical velocity
                    // Relocate
                    GLfloat penetration = m_ball->Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        m_ball->Position.y -= penetration;  // Move ball bback up
                    else
                        m_ball->Position.y += penetration;  // Move ball back down
                }
            }
        }
    }
    // Also check collisions for player pad (unless stuck)
    Collision result = CheckCollision(*m_ball, *m_player);
    if (!m_ball->Stuck && std::get<0>(result))
    {
        // Check where it hit the board, and change velocity based on where it hit the board
        GLfloat centerBoard = m_player->Position.x + m_player->Size.x / 2;
        GLfloat distance    = (m_ball->Position.x + m_ball->Radius) - centerBoard;
        GLfloat percentage  = distance / (m_player->Size.x / 2);
        // Then move accordingly
        GLfloat strength      = 2.0f;
        glm::vec2 oldVelocity = m_ball->Velocity;
        m_ball->Velocity.x      = INITIAL_BALL_VELOCITY.x * percentage * strength;
        // m_ball->Velocity.y = -m_ball->Velocity.y;
        m_ball->Velocity
            = glm::normalize(m_ball->Velocity)
              * glm::length(oldVelocity);  // Keep speed consistent over both axes (multiply by length
                                           // of old velocity, so total strength is not changed)
        // Fix sticky paddle
        m_ball->Velocity.y = -1 * abs(m_ball->Velocity.y);
    }
}
