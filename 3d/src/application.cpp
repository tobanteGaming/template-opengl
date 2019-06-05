#include "application.hpp"
#include "resource_manager.hpp"
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
Application::Application(std::string name) : m_name(name) {}

Application::~Application()
{
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
    m_window = glfwCreateWindow(1280, 720, m_name.c_str(), nullptr, nullptr);
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
    glViewport(0, 0, 1280, 720);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}
void Application::Run()
{
    // Load shaders
    ResourceManager::LoadShader(R"(3d\shader\vertex.glsl)",
                                R"(3d\shader\fragment.glsl)", nullptr, "main");
    ResourceManager::LoadTexture(R"(texture\awesomeface.png)", GL_TRUE, "face");

    // m_shaderProgram.reset(new Shader(VERTEX_SHADER_SRC,
    // FRAGMENT_SHADER_SRC));
    m_loader.reset(new ModelLoader());

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    std::vector<GLfloat> vertices = {
        -0.5f, 0.5f,  0.0f,  // v0
        -0.5f, -0.5f, 0.0f,  // v1
        0.5f,  -0.5f, 0.0f,  // v2
        0.5f,  0.5f,  0.0f,  // v3
    };

    std::vector<GLuint> indices = {
        0, 1, 3,  // top left triangle (v0, v1, v3)
        3, 1, 2   // bottom right triangle (v3, v1, v2)
    };

    auto model = m_loader->loadToVertexArray(vertices, indices);

    while (!glfwWindowShouldClose(m_window))
    {
        // Events
        glfwPollEvents();

        // Calculate delta time
        GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
        deltaTime            = currentFrame - lastFrame;
        lastFrame            = currentFrame;

        // Manage user input

        // Update Game state

        // Render
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ResourceManager::GetShader("main").Activate();
        
		glActiveTexture(GL_TEXTURE0);
        ResourceManager::GetTexture("face").Bind();
        Renderer::Draw(model);
        ResourceManager::GetShader("main").Deactivate();

        glfwSwapBuffers(m_window);
    }
}
}  // namespace tobanteGaming