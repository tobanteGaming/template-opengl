#pragma once

namespace tobanteGaming
{
constexpr struct
{
  float x, y;
  float r, g, b;
} vertices[3] = {
  {-0.6f, -0.4f, 1.f, 0.f, 0.f}, {0.6f, -0.4f, 0.f, 1.f, 0.f}, {0.f, 0.6f, 0.f, 0.f, 1.f}};

constexpr char* vertex_shader_text = R"(
    #version 330 core
    
    attribute vec3 vCol;
    attribute vec2 vPos;
    
    uniform mat4 MVP;
    varying vec3 color;

    void main()
    {
        gl_Position = MVP * vec4(vPos, 0.0, 1.0);
        color = vCol;
    };
)";

constexpr char* fragment_shader_text = R"(
    #version 330 core

    varying vec3 color;
    
    void main()
    {
        gl_FragColor = vec4(color, 1.0);
    }
)";

} // namespace tobanteGaming