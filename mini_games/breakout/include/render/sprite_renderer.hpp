#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render/shader.hpp"
#include "render/texture.hpp"

class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader& s);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(Texture2D& texture, glm::vec2 position,
                    glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));

private:
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();

private:
    // Render state
    Shader m_shader;
    GLuint m_quadVAO;
};