/**
 * https://learnopengl.com/Introduction
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "obj_loader.hpp"
#include "settings.hpp"
#include "shader.hpp"
#include "shader_source.hpp"
#include "shape/cube.hpp"
#include "shape/shape.hpp"
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
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });
    // RESIZE
    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow* window, int width, int height) {
            tobanteGaming::ignoreUnused(window);
            glViewport(0, 0, width, height);
        });

    Shader ourShader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
    tobanteGaming::Shape shape {};
    tobanteGaming::Cube cube {};

    // Initialize Loader
    objl::Loader Loader;

    // Load .obj File
    bool loadout
        = Loader.LoadFile(std::string(RESOURCE_PATH) + R"(obj\box_stack.obj)");

    // If so continue
    if (loadout)
    {
        // Create/Open e1Out.txt
        std::ofstream file("e1Out.txt");

        // Go through each loaded mesh and out its contents
        for (std::size_t i = 0; i < Loader.LoadedMeshes.size(); i++)
        {
            // Copy one of the loaded meshes to be our current mesh
            objl::Mesh curMesh = Loader.LoadedMeshes[i];

            // Print Mesh Name
            file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

            // Print Vertices
            file << "Vertices:\n";

            // Go through each vertex and print its number,
            //  position, normal, and texture coordinate
            for (std::size_t j = 0; j < curMesh.Vertices.size(); j++)
            {
                file << "V" << j << ": "
                     << "P(" << curMesh.Vertices[j].Position.X << ", "
                     << curMesh.Vertices[j].Position.Y << ", "
                     << curMesh.Vertices[j].Position.Z << ") "
                     << "N(" << curMesh.Vertices[j].Normal.X << ", "
                     << curMesh.Vertices[j].Normal.Y << ", "
                     << curMesh.Vertices[j].Normal.Z << ") "
                     << "TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", "
                     << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
            }

            // Print Indices
            file << "Indices:\n";

            // Go through every 3rd index and print the
            //	triangle that these indices represent
            for (std::size_t j = 0; j < curMesh.Indices.size(); j += 3)
            {
                file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", "
                     << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2]
                     << "\n";
            }

            // Print Material
            file << "Material: " << curMesh.MeshMaterial.name << "\n";
            file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", "
                 << curMesh.MeshMaterial.Ka.Y << ", "
                 << curMesh.MeshMaterial.Ka.Z << "\n";
            file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", "
                 << curMesh.MeshMaterial.Kd.Y << ", "
                 << curMesh.MeshMaterial.Kd.Z << "\n";
            file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", "
                 << curMesh.MeshMaterial.Ks.Y << ", "
                 << curMesh.MeshMaterial.Ks.Z << "\n";
            file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
            file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
            file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
            file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
            file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka
                 << "\n";
            file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd
                 << "\n";
            file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks
                 << "\n";
            file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
            file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

            // Leave a space to separate from the next mesh
            file << "\n";
        }

        // Close File
        file.close();
    }
    // If not output an error
    else
    {
        // Create/Open e1Out.txt
        std::ofstream file("e1Out.txt");

        // Output Error
        file << "Failed to Load File. May have failed to find it or it was not "
                "an .obj file.\n";

        // Close File
        file.close();
    }

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1
    // unit <-> 100 units
    glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);

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

    double lastTime = glfwGetTime();
    int nbFrames    = 0;
    // MAIN LOOP
    while (glfwWindowShouldClose(window) == 0)
    {
        // FPS
        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0)
        {  // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Triangle Color
        ourShader.use();
        const auto timeValue   = static_cast<float>(glfwGetTime());
        const float greenValue = sin(timeValue) / 2.0f + 0.5f;
        ourShader.setFloat4("ourColor", greenValue);
        ourShader.setMatrix4("MVP", mvp);

        // Draw triangle
        // shape.render();
        cube.render();

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}