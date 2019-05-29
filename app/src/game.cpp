#include "game.hpp"
#include "resource_manager.hpp"

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game() {}

void Game::Init() {}

void Game::Update(GLfloat dt) {}

void Game::ProcessInput(GLfloat dt) {}

void Game::Render() {}
