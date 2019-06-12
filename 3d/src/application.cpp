#include "application.hpp"

namespace tobanteGaming
{
Application::Application(String name) : m_name(name) {}

Application::~Application() {}

void Application::Init()
{
    // glfw, glew, imgui & callbacks
    m_window.reset(new Window());
    m_window->init();

    // Shader
    m_shader.reset(new Shader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE));

    // Object
    m_cube.reset(new Cube());
}
void Application::Run()
{
    const auto f_width  = static_cast<float>(WIDTH);
    const auto f_height = static_cast<float>(HEIGHT);
    const auto fov      = glm::radians(45.0f);

    // 45° FOV, 4:3 ratio, display range : 0.1 unit <-> 100 units
    auto projection = glm::perspective(fov, f_width / f_height, 0.1f, 100.0f);

    // Time & frame count for animation
    double lastTime = glfwGetTime();
    int nbFrames    = 0;

    // Main loop
    while (m_window->isOpen())
    {

        // FPS
        auto currentTime = static_cast<float>(glfwGetTime());
        nbFrames++;

        // If last print was more than 1 sec ago
        if (currentTime - lastTime >= 1.0)
        {
            LOG_INFO("{} fps", ImGui::GetIO().Framerate);
            nbFrames = 0;
            lastTime += 1.0;
        }

        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Color
        const float greenValue = sin(currentTime) / 2.0f + 0.5f;
        m_shader->use();
        m_shader->setFloat4("ourColor", greenValue);

        // Camera matrix
        glm::mat4 view = glm::lookAt(
            glm::vec3(nbFrames / currentTime, 2 * nbFrames / currentTime, 3),
            glm::vec3(0, 0, 0),  // Looks at the origin
            glm::vec3(0, 1, 0)   // Head is up
        );

        // Iidentity matrix (model will be at the origin)
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp   = projection * view * model;
        m_shader->setMatrix4("MVP", mvp);

        // Render
        m_cube->render();
        drawImgui();
        m_window->swapBuffers();
    }
}

void Application::openGLInit() {}

void Application::imguiInit() {}

void Application::registerCallbacks() {}

void Application::drawImgui()
{
    // New frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static float f = 0.0f;
    ImGui::Begin("Test");
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::ColorEdit3("clear color", (float*)&clear_color);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    // Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
}  // namespace tobanteGaming