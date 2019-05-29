#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>

/**
 * @brief Represents an OpenGL program (vertex & fragment shader)
 */
class Shader
{
private:
    unsigned int m_id;

public:
    /**
     * @brief Constructor
     *
     * Takes sources for a vertex & fragment shader
     */
    Shader(const char* vertexSource, const char* fragmentSource)
    {
        // Vertex
        unsigned int vertex;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // Fragment
        unsigned int fragment;
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSource, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // Program
        m_id = glCreateProgram();
        glAttachShader(m_id, vertex);
        glAttachShader(m_id, fragment);
        glLinkProgram(m_id);
        checkCompileErrors(m_id, "PROGRAM");

        // Delete the shaders as they're linked into our program now and no
        // longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    /**
     * @brief Activates the shader
     */
    void use() { glUseProgram(m_id); }

    /**
     * @brief Returns the id
     */
    unsigned int getID() { return m_id; }

    /**
     * @brief Sets a uniform bool
     */
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }

    /**
     * @brief Sets a uniform int
     */
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    /**
     * @brief Sets a uniform float
     */
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    /**
     * @brief Sets a uniform float vector4
     */
    void setFloat4(const std::string& name, float value) const
    {
        glUniform4f(glGetUniformLocation(m_id, name.c_str()), 0.0f, value, 0.0f,
                    1.0f);
    }

private:
    void checkCompileErrors(unsigned int shader_id, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader_id, 1024, nullptr, infoLog);
                std::string err = "ERROR::SHADER_COMPILATION_ERROR of type: ";
                std::cout << err << type << "\n" << infoLog << '\n';
            }
        }
        else
        {
            glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader_id, 1024, nullptr, infoLog);
                std::string err = "ERROR::PROGRAM_LINKING_ERROR of type: ";
                std::cout << err << type << "\n" << infoLog << '\n';
            }
        }
    }
};