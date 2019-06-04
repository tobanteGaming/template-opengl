#include <cstdlib>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "resource_manager.hpp"
#include "settings.hpp"
#include "util.hpp"

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode);

std::unique_ptr<Game> Breakout;

int main(int argc, char* argv[])
{
    ignoreUnused(argc);
    ignoreUnused(argv);
    glfwInit();

    GLFWmonitor* monitor    = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height,
                                          rr::GAME_NAME, monitor, NULL);
    // GLFWwindow* window = glfwCreateWindow(rr::DEFAULT_SCREEN_WIDTH,
    // rr::DEFAULT_SCREEN_HEIGHT,
    //                                       rr::GAME_NAME, nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();  // Call it once to catch glewInit() bug, all other errors are
                   // now from our application.

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow* window, int width, int height) {
            ignoreUnused(window);
            glViewport(0, 0, width, height);
        });

    // OpenGL configuration
    glViewport(0, 0, mode->width, mode->height);
    // glViewport(0, 0, rr::DEFAULT_SCREEN_WIDTH, rr::DEFAULT_SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize game
    Breakout = std::make_unique<Game>(mode->width, mode->height);
    // Breakout = std::make_unique<Game>(rr::DEFAULT_SCREEN_WIDTH,
    // rr::DEFAULT_SCREEN_HEIGHT);
    Breakout->Init();

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
        deltaTime            = currentFrame - lastFrame;
        lastFrame            = currentFrame;
        glfwPollEvents();

        // deltaTime = 0.001f;
        // Manage user input
        Breakout->ProcessInput(deltaTime);

        // Update Game state
        Breakout->Update(deltaTime);

        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout->Render();

        glfwSwapBuffers(window);
    }

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    glfwTerminate();
    return EXIT_SUCCESS;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode)
{
    ignoreUnused(mode);
    ignoreUnused(scancode);

    // When a user presses the escape key, we set the WindowShouldClose property
    // to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout->Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            Breakout->Keys[key] = GL_FALSE;
    }
}
