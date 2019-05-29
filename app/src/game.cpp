#include <iostream>

#include "game.hpp"

#include "collision.hpp"
#include "resource_manager.hpp"

Game::Game(GLuint width, GLuint height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader(R"(shaders\sprite_vs.glsl)", R"(shaders\sprite_fs.glsl)", nullptr,
                                "sprite");
    // Configure shaders
    const auto f_width  = static_cast<float>(Width);
    const auto f_height = static_cast<float>(Height);
    auto projection     = glm::ortho(0.0f, f_width, f_height, 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // Load textures
    ResourceManager::LoadTexture(R"(texture\background.jpg)", GL_FALSE, "background");
    ResourceManager::LoadTexture(R"(texture\awesomeface.png)", GL_TRUE, "face");
    ResourceManager::LoadTexture(R"(texture\block.png)", GL_FALSE, "block");
    ResourceManager::LoadTexture(R"(texture\block_solid.png)", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture(R"(texture\paddle.png)", true, "paddle");

    // Set render-specific controls
    Renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));

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
    Ball->Move(dt, Width);
    DoCollisions();
}

void Game::ProcessInput(GLfloat dt)
{
    if (State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0)
            {
                Player->Position.x -= velocity;
                if (Ball->Stuck) Ball->Position.x -= velocity;
            }
        }
        if (Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Ball->Stuck) Ball->Position.x += velocity;
            }
        }
        if (Keys[GLFW_KEY_SPACE]) Ball->Stuck = false;
    }
}

void Game::Render()
{
    if (State == GAME_ACTIVE)
    {
        // Draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0),
                             glm::vec2(Width, Height), 0.0f);
        // Draw level
        Levels[Level].Draw(*Renderer);

        // Draw entities
        Player->Draw(*Renderer);
        Ball->Draw(*Renderer);
    }
}

void Game::DoCollisions()
{
    for (GameObject& box : this->Levels[this->Level].Bricks)
    {
        if (!box.Destroyed)
        {
            if (CheckCollision(*Ball, box))
            {
                if (!box.IsSolid) box.Destroyed = GL_TRUE;
            }
        }
    }
}