#include "render/window.hpp"

namespace tobanteGaming
{

Window::~Window()
{
    // imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::init()
{
    // glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "tobanteGaming: 3D", nullptr,
                                nullptr);
    if (m_window == nullptr)
    {
        LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);

    // glew
    if (glewInit() != GLEW_OK)
    {
        LOG_ERROR("Error in glew init");
    }
    LOG_INFO("OpenGL: {}", glGetString(GL_VERSION));

    // imgui
    const char* glsl_version = "#version 430";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Keys
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode,
                                    int action, int mods) {
        tobanteGaming::ignoreUnused(scancode);
        tobanteGaming::ignoreUnused(mods);
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });

    // Resize
    glfwSetFramebufferSizeCallback(
        m_window, [](GLFWwindow* window, int width, int height) {
            tobanteGaming::ignoreUnused(window);
            glViewport(0, 0, width, height);
        });
}

}  // namespace tobanteGaming