#pragma once

#include <array>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "entity/entity.hpp"
#include "render/particle.hpp"
#include "render/sprite.hpp"

/**
 * @brief Represents the current state of the game.
 */
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

namespace tobanteGaming
{
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

    void ProcessInput(GLfloat dt);

    void Update(GLfloat dt);

    void Render();

public:
    static std::array<bool, 1024> Keys;

private:
    void DoCollisions();
    // Reset
    void ResetLevel();
    void ResetPlayer();

private:
    /**
     * @brief Game state.
     */
    GameState m_state;
    GLuint m_width, m_height;

    // Game-related State data
    std::unique_ptr<SpriteRenderer> m_renderer;
    std::unique_ptr<tobanteGaming::Entity> m_player;
    std::unique_ptr<ParticleGenerator> m_particles;
    using Wall = std::vector<std::unique_ptr<tobanteGaming::Entity>>;
    Wall m_wall_left;
    Wall m_wall_right;
};

}  // namespace tobanteGaming