#include <iostream>

#include "shader.hpp"

Shader& Shader::Activate()
{
    glUseProgram(ID);
    return *this;
}

void Shader::Deactivate() { glUseProgram(0); }

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource,
                     const GLchar* geometrySource)
{
    GLuint sVertex, sFragment, gShader;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // If geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, sVertex);
    glAttachShader(ID, sFragment);
    if (geometrySource != nullptr) glAttachShader(ID, gShader);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer
    // necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr) glDeleteShader(gShader);
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
    if (useShader) Activate();
    glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader)
{
    if (useShader) Activate();
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y,
                         GLboolean useShader)
{
    if (useShader) Activate();
    glUniform2f(glGetUniformLocation(ID, name), x, y);
}
void Shader::SetVector2f(const GLchar* name, const glm::vec2& value,
                         GLboolean useShader)
{
    if (useShader) Activate();
    glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}
void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z,
                         GLboolean useShader)
{
    if (useShader) Activate();
    glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}
void Shader::SetVector3f(const GLchar* name, const glm::vec3& value,
                         GLboolean useShader)
{
    if (useShader) Activate();
    glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z,
                         GLfloat w, GLboolean useShader)
{
    if (useShader) Activate();
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}
void Shader::SetVector4f(const GLchar* name, const glm::vec4& value,
                         GLboolean useShader)
{
    if (useShader) Activate();
    glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z,
                value.w);
}
void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix,
                        GLboolean useShader)
{
    if (useShader) Activate();
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE,
                       glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout
                << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog
                << "\n -- --------------------------------------------------- "
                   "-- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout
                << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog
                << "\n -- --------------------------------------------------- "
                   "-- "
                << std::endl;
        }
    }
}