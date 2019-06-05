#pragma once

// BASIC
constexpr char* VERTEX_SHADER_SOURCE = R"(
    #version 430 core

    layout (location = 0) in vec3 vertexPosition_modelspace;

    // Values that stay constant for the whole mesh.
    uniform mat4 MVP;

    void main(){
        // Output position of the vertex, in clip space : MVP * position
        gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
    }
)";

constexpr char* FRAGMENT_SHADER_SOURCE = R"(
    #version 430 core

    out vec4 FragColor;

    uniform vec4 ourColor;

    void main()
    {
        FragColor = ourColor;
    }
)";
