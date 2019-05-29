#include <iostream>

#include "game.hpp"
#include "render/sprite_renderer.hpp"
#include "resource_manager.hpp"

// Game-related State data
SpriteRenderer* Renderer;

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game() { delete Renderer; }

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\shaders\sprite_vs.glsl)",
        R"(C:\Dev\tobanteGaming\tests\template-opengl\shaders\sprite_fs.glsl)",
        nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection
        = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
                     static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture(
        R"(C:\Dev\tobanteGaming\tests\template-opengl\resources\texture\awesomeface.png)",
        GL_TRUE, "face");
    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

void Game::Update(GLfloat dt) {}

void Game::ProcessInput(GLfloat dt) {}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"),
                         glm::vec2(200, 200), glm::vec2(300, 400), 45.0f,
                         glm::vec3(0.0f, 1.0f, 0.0f));
}
