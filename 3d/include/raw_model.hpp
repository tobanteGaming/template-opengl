#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace tobanteGaming
{
class RawModel
{
public:
    RawModel(GLuint id, GLuint vertexCount)
        : m_id(id), m_vertexCount(vertexCount)
    {
    }

    GLuint getID() { return m_id; }
    GLuint getVertexCount() { return m_vertexCount; }

private:
    GLuint m_id;
    GLuint m_vertexCount;
};

}  // namespace tobanteGaming