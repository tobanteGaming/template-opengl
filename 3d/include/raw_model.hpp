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

class ModelLoader
{
public:
    ~ModelLoader()
    {
        for (const auto vao : m_vaos)
        {
            glDeleteVertexArrays(1, &vao);
        }
        for (const auto vbo : m_vbos)
        {
            glDeleteBuffers(1, &vbo);
        }
    }

    RawModel loadToVertexArray(std::vector<GLfloat> positions)
    {
        auto vao = createVertexArray();
        storeDataInAttributeList(0, positions);
        unbindVertexArray();
        return RawModel(vao, positions.size());
    }

private:
    GLuint createVertexArray()
    {
        GLuint vaoID;
        glGenVertexArrays(1, &vaoID);
        m_vaos.emplace_back(vaoID);
        glBindVertexArray(vaoID);
        return vaoID;
    }

    void storeDataInAttributeList(int attributeNumber,
                                  std::vector<GLfloat> data)
    {
        /* Allocate and assign two Vertex Buffer Objects to our handle */
        GLuint vboID;
        glGenBuffers(1, &vboID);
        m_vbos.emplace_back(vboID);

        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0],
                     GL_STATIC_DRAW);

        glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // glEnableVertexAttribArray(attributeNumber);
    }
    void unbindVertexArray() { glBindVertexArray(0); }

private:
    std::vector<GLuint> m_vaos;
    std::vector<GLuint> m_vbos;
};

class Renderer
{
public:
    static void Draw(RawModel& model)
    {
        glBindVertexArray(model.getID());
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
};
}  // namespace tobanteGaming