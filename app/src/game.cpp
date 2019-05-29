#include <iostream>

#include "game.hpp"

#include "entity/game_object.hpp"
#include "render/sprite_renderer.hpp"
#include "resource_manager.hpp"

// Game-related State data
SpriteRenderer* Renderer;
GameObject* Player;

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete Renderer;
    delete Player;
}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\shaders\sprite_vs.glsl)",
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\shaders\sprite_fs.glsl)",
        nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection
        = glm::ortho(0.0f, static_cast<GLfloat>(Width),
                     static_cast<GLfloat>(Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // Load textures
    ResourceManager::LoadTexture(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\texture\background.jpg)",
        GL_FALSE, "background");
    ResourceManager::LoadTexture(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\texture\awesomeface.png)",
        GL_TRUE, "face");
    ResourceManager::LoadTexture(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\texture\block.png)",
        GL_FALSE, "block");
    ResourceManager::LoadTexture(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\texture\block_solid.png)",
        GL_FALSE, "block_solid");
    ResourceManager::LoadTexture(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\texture\paddle.png)",
        true, "paddle");

    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    // Load levels
    GameLevel one;
    one.Load(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\levels\001.lvl)",
        Width, Height * 0.5);
    GameLevel two;
    two.Load(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\levels\002.lvl)",
        Width, Height * 0.5);
    GameLevel three;
    three.Load(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\levels\003.lvl)",
        Width, Height * 0.5);
    GameLevel four;
    four.Load(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\levels\004.lvl)",
        Width, Height * 0.5);
    Levels.push_back(one);
    Levels.push_back(two);
    Levels.push_back(three);
    Levels.push_back(four);
    Level = 0;
    // Configure game objects
    glm::vec2 playerPos
        = glm::vec2(Width / 2 - PLAYER_SIZE.x / 2, Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE,
                            ResourceManager::GetTexture("paddle"));
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
            if (Player->Position.x <= Width - Player->Size.x)
                Player->Position.x += velocity;
        }
    }
}

void Game::Render()
{
    if (State == GAME_ACTIVE)
    {
        // Draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"),
                             glm::vec2(0, 0), glm::vec2(Width, Height), 0.0f);
        // Draw level
        Levels[Level].Draw(*Renderer);
        // Draw player
        Player->Draw(*Renderer);
    }
}