#pragma once

#include "core/common.hpp"

/**
 * @brief Represents an OpenGL program (vertex & fragment shader)
 */
class Shader
{
public:
    /**
     * @brief Constructor
     *
     * Takes sources for a vertex & fragment shader
     */
    Shader(const char* vertexSource, const char* fragmentSource);

    /**
     * @brief Activates the shader
     */
    void use();

    /**
     * @brief Returns the id
     */
    unsigned int getID() const;

    /**
     * @brief Sets a uniform bool
     */
    void setBool(const std::string& name, bool value) const;

    /**
     * @brief Sets a uniform int
     */
    void setInt(const std::string& name, int value) const;

    /**
     * @brief Sets a uniform float
     */
    void setFloat(const std::string& name, float value) const;

    /**
     * @brief Sets a uniform float vector4
     */
    void setFloat4(const std::string& name, float value) const;

    /**
     * @brief Sets a uniform float glm::mat4
     */
    void setMatrix4(const std::string& name, glm::mat4 value) const;

private:
    void checkCompileErrors(unsigned int shader_id, std::string type);

private:
    unsigned int m_id;
};