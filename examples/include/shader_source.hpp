#pragma once

// BASIC
constexpr const char* VERTEX_SHADER_SOURCE = R"(
    #version 330 core

    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

constexpr const char* FRAGMENT_SHADER_SOURCE = R"(
    #version 330 core

    out vec4 FragColor;

    uniform vec4 ourColor;

    void main()
    {
        FragColor = ourColor;
    }
)";

// TEXTURE
constexpr const char* TEXTURE_VERTEX_SHADER_SOURCE = R"(
    #version 330 core

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

constexpr const char* TEXTURE_FRAGMENT_SHADER_SOURCE = R"(
    #version 330 core

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