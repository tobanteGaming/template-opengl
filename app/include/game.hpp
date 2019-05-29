#pragma once

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "collision.hpp"
#include "entity/ball_object.hpp"
#include "entity/game_object.hpp"
#include "game_level.hpp"
#include "render/sprite_renderer.hpp"

/**
 * @brief Represents the current state of the game.
 */
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

/**
 * @brief Game holds all game-related state and functionality.
 *
 * Combines all game-related data into a single class for easy access to each of
 * the components and manageability.
 */
class Game
{
public:
    /**
     * @brief Constructor.
     */
    Game(GLuint width, GLuint height);

    /**
     * @brief Destructor.
     */
    ~Game() = default;

    /**
     * @brief Initialize game state (load all shaders/textures/levels).
     */
    void Init();
    // GameLoop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();

public:
    /**
     * @brief Game state.
     */
    GameState State;
    GLboolean Keys[1024];
    GLuint Width, Height;

    std::vector<GameLevel> Levels;
    GLuint Level;

private:
    void DoCollisions();
    // Reset
    void ResetLevel();
    void ResetPlayer();

private:
    // Game-related State data
    std::unique_ptr<SpriteRenderer> Renderer;
    std::unique_ptr<GameObject> Player;
    std::unique_ptr<BallObject> Ball;
};
