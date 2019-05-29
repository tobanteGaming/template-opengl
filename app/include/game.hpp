#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game_level.hpp"
/**
 * @brief Represents the current state of the game.
 */
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);

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
    ~Game();
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
};
