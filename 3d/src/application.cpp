#include "application.hpp"

namespace tobanteGaming
{
Application::Application(String name) : m_name(name) {}

Application::~Application()
{
    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
}

void Application::Init()
{
    // GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // WINDOW
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "3D", nullptr, nullptr);
    if (m_window == nullptr)
    {
        LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);

    // GLEW
    if (glewInit() != GLEW_OK)
    {
        LOG_ERROR("Error in glew init");
    }
    LOG_INFO("OpenGL: {}", glGetString(GL_VERSION));

    // IMGUI
    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(m_window, false);

    // CALLBACKS
    // KEYS
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode,
                                    int action, int mods) {
        tobanteGaming::ignoreUnused(scancode);
        tobanteGaming::ignoreUnused(mods);
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });
    // RESIZE
    glfwSetFramebufferSizeCallback(
        m_window, [](GLFWwindow* window, int width, int height) {
            tobanteGaming::ignoreUnused(window);
            glViewport(0, 0, width, height);
        });

    // SHader
    ourShader.reset(new Shader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE));

    cube.reset(new Cube());
}
void Application::Run()
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1
    // unit <-> 100 units
    glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);

    // Or, for an ortho camera :
    // glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
    // // In world coordinates

    double lastTime = glfwGetTime();
    int nbFrames    = 0;
    // MAIN LOOP
    while (glfwWindowShouldClose(m_window) == 0)
    {
        // IMGUI
        ImGui_ImplGlfwGL3_NewFrame();

        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears
        // in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }

        // 2. Show another simple window, this time using an explicit Begin/End
        // pair
        if (show_another_window)
        {
            ImGui::SetNextWindowSize(ImVec2(200, 100),
                                     ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello");
            ImGui::End();
        }

        // 3. Show the ImGui test window. Most of the sample code is in
        // ImGui::ShowTestWindow()
        if (show_test_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&show_test_window);
        }

        // FPS
        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0)
        {
            // If last prinf() was more than 1 sec ago
            LOG_INFO("{} ms/frame", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Triangle Color
        ourShader->use();
        const auto timeValue   = static_cast<float>(glfwGetTime());
        const float greenValue = sin(timeValue) / 2.0f + 0.5f;
        ourShader->setFloat4("ourColor", greenValue);

        // Camera matrix
        glm::mat4 View = glm::lookAt(
            glm::vec3(nbFrames / timeValue, 2 * nbFrames / timeValue,
                      3),        // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0),  // and looks at the origin
            glm::vec3(0, 1,
                      0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices
        // Remember, matrix multiplication is the other way around
        glm::mat4 mvp = Projection * View * Model;
        ourShader->setMatrix4("MVP", mvp);

        // Draw triangle
        // shape.render();
        cube->render();
        ImGui::Render();

        // Check and call events and swap the buffers
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

}  // namespace tobanteGaming