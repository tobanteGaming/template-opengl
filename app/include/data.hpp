#pragma once

namespace tobanteGaming
{
static const struct
{
  float x, y;
  float r, g, b;
} vertices[3] = {{-0.6f, -0.4f, 1.f, 0.f, 0.f},
                 {0.6f, -0.4f, 0.f, 1.f, 0.f},
                 {0.f, 0.6f, 0.f, 0.f, 1.f}};

static const char* vertex_shader_text =
  "#version 110\n"
  "uniform mat4 MVP;\n"
  "attribute vec3 vCol;\n"
  "attribute vec2 vPos;\n"
  "varying vec3 color;\n"
  "void main()\n"
  "{\n"
  "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
  "    color = vCol;\n"
  "}\n";

static const char* fragment_shader_text =
  "#version 110\n"
  "varying vec3 color;\n"
  "void main()\n"
  "{\n"
  "    gl_FragColor = vec4(color, 1.0);\n"
  "}\n";
} // namespace tobanteGaming