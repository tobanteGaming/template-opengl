#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "texture.hpp"

class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader& s);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10),
                    GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    // Render state
    Shader shader;
    GLuint quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};