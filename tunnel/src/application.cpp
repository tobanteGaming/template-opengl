#include "application.hpp"
#include "resource_manager.hpp"
#include "util.hpp"

void key_callback_func(GLFWwindow* window, int key, int scancode, int action,
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
        // if (action == GLFW_PRESS)
        //     Breakout->Keys[key] = GL_TRUE;
        // else if (action == GLFW_RELEASE)
        //     Breakout->Keys[key] = GL_FALSE;
    }
}

namespace tobanteGaming
{
Application::Application(std::string name) : m_name(name) {}

Application::~Application()
{
    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    glfwTerminate();
}

void Application::Init()
{
    glfwInit();

    GLFWmonitor* monitor    = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    m_window = glfwCreateWindow(mode->width, mode->height, m_name.c_str(),
                                monitor, NULL);

    glfwMakeContextCurrent(m_window);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();  // Call it once to catch glewInit() bug, all other errors are
                   // now from our application.

    glfwSetKeyCallback(m_window, key_callback_func);
    glfwSetFramebufferSizeCallback(
        m_window, [](GLFWwindow* window, int width, int height) {
            ignoreUnused(window);
            glViewport(0, 0, width, height);
        });

    // OpenGL configuration
    glViewport(0, 0, mode->width, mode->height);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize game
    Breakout = std::make_unique<Game>(mode->width, mode->height);
    Breakout->Init();
}
void Application::Run()
{
    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    while (!glfwWindowShouldClose(m_window))
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

        glfwSwapBuffers(m_window);
    }
}
}  // namespace tobanteGaming