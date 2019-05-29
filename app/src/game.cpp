#include <iostream>

#include "game.hpp"

#include "resource_manager.hpp"

Game::Game(GLuint width, GLuint height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader(R"(shaders\sprite_vs.glsl)", R"(shaders\sprite_fs.glsl)", nullptr,
                                "sprite");
    ResourceManager::LoadShader(R"(shaders\particle_vs.glsl)", R"(shaders\particle_fs.glsl)", nullptr,
                                "particle");
    // Configure shaders
    const auto f_width  = static_cast<float>(Width);
    const auto f_height = static_cast<float>(Height);
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
    Renderer  = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    Particles = std::make_unique<ParticleGenerator>(ResourceManager::GetShader("particle"),
                                                    ResourceManager::GetTexture("particle"), 500);
    // Load levels
    GameLevel one;
    GameLevel two;
    GameLevel three;
    GameLevel four;
    one.Load(R"(levels\001.lvl)", Width, Height * 0.5);
    two.Load(R"(levels\002.lvl)", Width, Height * 0.5);
    three.Load(R"(levels\003.lvl)", Width, Height * 0.5);
    four.Load(R"(levels\004.lvl)", Width, Height * 0.5);
    Levels.push_back(one);
    Levels.push_back(two);
    Levels.push_back(three);
    Levels.push_back(four);

    Level = 0;

    // Configure game objects
    glm::vec2 playerPos = glm::vec2(Width / 2 - PLAYER_SIZE.x / 2, Height - PLAYER_SIZE.y);
    Player
        = std::make_unique<GameObject>(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    // Ball
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    Ball              = std::make_unique<BallObject>(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                                        ResourceManager::GetTexture("face"));
}

void Game::Update(GLfloat dt)
{
    // Update objects
    Ball->Move(dt, this->Width);
    // Check for collisions
    this->DoCollisions();
    // Update particles
    Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2));
    // Check loss condition
    if (Ball->Position.y >= this->Height)  // Did ball reach bottom edge?
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
}

void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0)
            {
                Player->Position.x -= velocity;
                if (Ball->Stuck) Ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Ball->Stuck) Ball->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE]) Ball->Stuck = false;
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // Draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0),
                             glm::vec2(this->Width, this->Height), 0.0f);
        // Draw level
        this->Levels[this->Level].Draw(*Renderer);
        // Draw player
        Player->Draw(*Renderer);
        // Draw particles
        Particles->Draw();
        // Draw ball
        Ball->Draw(*Renderer);
    }
}

void Game::ResetLevel()
{
    if (this->Level == 0)
        this->Levels[0].Load("levels/001.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 1)
        this->Levels[1].Load("levels/002.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 2)
        this->Levels[2].Load("levels/003.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 3)
        this->Levels[3].Load("levels/004.lvl", this->Width, this->Height * 0.5f);
}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    Player->Size     = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)),
                INITIAL_BALL_VELOCITY);
}

void Game::DoCollisions()
{
    for (GameObject& box : this->Levels[this->Level].Bricks)
    {
        if (!box.Destroyed)
        {
            Collision collision = CheckCollision(*Ball, box);
            if (std::get<0>(collision))  // If collision is true
            {
                // Destroy block if not solid
                if (!box.IsSolid) box.Destroyed = GL_TRUE;
                // Collision resolution
                Direction dir         = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT)  // Horizontal collision
                {
                    Ball->Velocity.x = -Ball->Velocity.x;  // Reverse horizontal velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        Ball->Position.x += penetration;  // Move ball to right
                    else
                        Ball->Position.x -= penetration;  // Move ball to left;
                }
                else  // Vertical collision
                {
                    Ball->Velocity.y = -Ball->Velocity.y;  // Reverse vertical velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        Ball->Position.y -= penetration;  // Move ball bback up
                    else
                        Ball->Position.y += penetration;  // Move ball back down
                }
            }
        }
    }
    // Also check collisions for player pad (unless stuck)
    Collision result = CheckCollision(*Ball, *Player);
    if (!Ball->Stuck && std::get<0>(result))
    {
        // Check where it hit the board, and change velocity based on where it hit the board
        GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
        GLfloat distance    = (Ball->Position.x + Ball->Radius) - centerBoard;
        GLfloat percentage  = distance / (Player->Size.x / 2);
        // Then move accordingly
        GLfloat strength      = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x      = INITIAL_BALL_VELOCITY.x * percentage * strength;
        // Ball->Velocity.y = -Ball->Velocity.y;
        Ball->Velocity
            = glm::normalize(Ball->Velocity)
              * glm::length(oldVelocity);  // Keep speed consistent over both axes (multiply by length
                                           // of old velocity, so total strength is not changed)
        // Fix sticky paddle
        Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
    }
}
