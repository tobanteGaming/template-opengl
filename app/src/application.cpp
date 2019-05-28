#include <stdlib.h>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "application.hpp"
#include "linmath.hpp"


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

Application::Application(std::string name)
  : m_name(name)
{
}

int Application::Run()
{
  GLFWwindow* window;

  glfwSetErrorCallback([](int error, const char* description) {
    std::cout << "Error: " << description << std::endl;
  });

  if (!glfwInit())
  {
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  window = glfwCreateWindow(1280, 720, m_name.c_str(), nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);


  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
  });

  // GLEW
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Error in glewInit" << std::endl;
  }
  // Get OpenGL version
  std::cout << glGetString(GL_VERSION) << std::endl;


  glfwSwapInterval(1);
  // NOTE: OpenGL error checks have been omitted for brevity
  GLuint vertex_buffer, vertex_shader, fragment_shader, program;
  GLint mvp_location, vpos_location, vcol_location;

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
  glCompileShader(vertex_shader);
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
  glCompileShader(fragment_shader);
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  mvp_location = glGetUniformLocation(program, "MVP");
  vpos_location = glGetAttribLocation(program, "vPos");
  vcol_location = glGetAttribLocation(program, "vCol");
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*)0);
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*)(sizeof(float) * 2));
  while (!glfwWindowShouldClose(window))
  {
    float ratio;
    int width, height;
    mat4x4 m, p, mvp;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);
    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
} // namespace tobanteGaming