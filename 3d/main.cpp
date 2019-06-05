/**
 * https://learnopengl.com/Introduction
 */

#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

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

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1
    // unit <-> 100 units
    glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    // Or, for an ortho camera :
    // glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
    // // In world coordinates

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3),  // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0),  // and looks at the origin
        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    // Remember, matrix multiplication is the other way around
    glm::mat4 mvp = Projection * View * Model;

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
        ourShader.setMatrix4("MVP", mvp);

        // Draw triangle
        shape.render();

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}