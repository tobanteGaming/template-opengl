#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "raw_model.hpp"

namespace tobanteGaming
{
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

    RawModel loadToVertexArray(const std::vector<GLfloat>& positions,
                               const std::vector<GLuint>& indices)
    {
        auto vao = createVertexArray();
        bindIndicesBuffer(indices);
        storeDataInAttributeList(0, positions);
        unbindVertexArray();
        return RawModel(vao, indices.size());
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
                                  const std::vector<GLfloat>& data)
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

    void bindIndicesBuffer(const std::vector<GLuint>& indices)
    {
        GLuint vboID;
        glGenBuffers(1, &vboID);
        m_vbos.push_back(vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                     &indices[0], GL_STATIC_DRAW);
    }

    void unbindVertexArray() { glBindVertexArray(0); }

private:
    std::vector<GLuint> m_vaos;
    std::vector<GLuint> m_vbos;
};

}  // namespace tobanteGaming