#include <iostream>

#include "game.hpp"

#include "entity/game_object.hpp"
#include "render/sprite_renderer.hpp"
#include "resource_manager.hpp"

// Game-related State data
SpriteRenderer* Renderer;
GameObject* Player;

Game::Game(GLuint width, GLuint height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

Game::~Game()
{
    delete Renderer;
    delete Player;
}

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
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

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
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(GLfloat dt) {}

void Game::ProcessInput(GLfloat dt)
{
    if (State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0) Player->Position.x -= velocity;
        }
        if (Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= Width - Player->Size.x) Player->Position.x += velocity;
        }
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
        // Draw player
        Player->Draw(*Renderer);
    }
}