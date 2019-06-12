#include "render/shader.hpp"

Shader::Shader(const char* vertexSource, const char* fragmentSource)
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

void Shader::use() { glUseProgram(m_id); }

unsigned int Shader::getID() const { return m_id; }

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat4(const std::string& name, float value) const
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), 0.0f, value, 0.0f,
                1.0f);
}

void Shader::setMatrix4(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE,
                       &value[0][0]);
}
void Shader::checkCompileErrors(unsigned int shader_id, std::string type)
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
            LOG_ERROR("{}{}\n{}", err, type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader_id, 1024, nullptr, infoLog);
            std::string err = "ERROR::PROGRAM_LINKING_ERROR of type: ";
            LOG_ERROR("{}{}\n{}", err, type, infoLog);
        }
    }
}
