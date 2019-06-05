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

// TEXTURE
constexpr char* TEXTURE_VERTEX_SHADER_SOURCE = R"(
    #version 430 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
	    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    }
)";

constexpr char* TEXTURE_FRAGMENT_SHADER_SOURCE = R"(
    #version 430 core

    out vec4 FragColor;

    in vec3 ourColor;
    in vec2 TexCoord;

    // texture samplers
    uniform sampler2D texture1;
    uniform sampler2D texture2;

    void main()
    {
        // linearly interpolate between both textures (80% container, 20% awesomeface)
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    }
)";