/**
 * https://learnopengl.com/Introduction
 */

#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "settings.hpp"
#include "shader.hpp"
#include "shader_source.hpp"
#include "shape.hpp"
#include "warning.hpp"

int main()
{
    // GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // WINDOW
    auto* window = glfwCreateWindow(WIDTH, HEIGHT, "3D", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error in glew init" << '\n';
    }
    std::cout << glGetString(GL_VERSION) << '\n';

    // CALLBACKS
    // KEYS
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                  int action, int mods) {
        tobanteGaming::ignoreUnused(scancode);
        tobanteGaming::ignoreUnused(mods);
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    });
    // RESIZE
    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow* window, int width, int height) {
            tobanteGaming::ignoreUnused(window);
            glViewport(0, 0, width, height);
        });

    Shader ourShader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
    tobanteGaming::Shape shape{};

    // STATS
    int nrAttr;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttr);
    std::cout << "Max # of vertex attributes supported: " << nrAttr << '\n';

    // MAIN LOOP
    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Triangle Color
        ourShader.use();
        const float timeValue  = static_cast<float>(glfwGetTime());
        const float greenValue = sin(timeValue) / 2.0f + 0.5f;
        ourShader.setFloat4("ourColor", greenValue);

        // Draw triangle
        shape.render();

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}