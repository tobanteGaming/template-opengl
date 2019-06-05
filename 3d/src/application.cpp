#include "application.hpp"
#include "warning.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode)
{
    namespace tg = tobanteGaming;
    tg::ignoreUnused(mode);
    tg::ignoreUnused(scancode);

    // When a user presses the escape key, we set the WindowShouldClose property
    // to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            // tg::Game::Keys[key] = GL_TRUE;
        }

        if (action == GLFW_RELEASE)
        {
            // tg::Game::Keys[key] = GL_FALSE;
        }
    }
}

namespace tobanteGaming
{
Application::Application(std::string name) : m_name(name)
{
    // m_loader.reset(new tobanteGaming::ModelLoader());
}

Application::~Application() { glfwTerminate(); }

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

    glfwSetKeyCallback(m_window, key_callback);
    glfwSetFramebufferSizeCallback(
        m_window, [](GLFWwindow* window, int width, int height) {
            ignoreUnused(window);
            glViewport(0, 0, width, height);
        });

    // OpenGL configuration
    glViewport(0, 0, mode->width, mode->height);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void Application::Run()
{
    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    std::vector<GLfloat> vertices = {
        // Left bottom triangle
        -0.5f, 0.5f, 0.0f,   //
        -0.5f, -0.5f, 0.0f,  //
        0.5f, -0.5f, 0.0f,   //

        // Right top triangle
        0.5f, -0.5f, 0.0f,  //
        0.5f, 0.5f, 0.0f,   //
        -0.5f, 0.5f, 0.0f   //
    };

    auto model = m_loader.loadToVertexArray(vertices);

    while (!glfwWindowShouldClose(m_window))
    {
        // Calculate delta time
        GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
        deltaTime            = currentFrame - lastFrame;
        lastFrame            = currentFrame;
        glfwPollEvents();

        // Manage user input

        // Update Game state

        // Render
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer::Draw(model);

        glfwSwapBuffers(m_window);
    }
}
}  // namespace tobanteGaming