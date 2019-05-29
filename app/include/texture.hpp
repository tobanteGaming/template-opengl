#pragma once

#include <GL/glew.h>

/**
 * @brief Texture2D is able to store and configure a texture in OpenGL. It also
 * hosts utility functions for easy management.
 */
class Texture2D
{
public:
    /**
     * @brief Constructor (sets default texture modes).
     */
    Texture2D();

    /**
     * @brief Generates texture from image data.
     */
    void Generate(GLuint width, GLuint height, unsigned char* data);

    /**
     * @brief Binds the texture as the current active GL_TEXTURE_2D texture
     * object.
     */
    void Bind() const;

public:
    /**
     * @brief Holds the ID of the texture object, used for all texture
     * operations to reference to this particlar texture.
     */
    GLuint ID;

    /**
     * @brief Width of loaded image in pixels.
     */
    GLuint Width;

    /**
     * @brief Height of loaded image in pixels.
     */
    GLuint Height;

    /**
     * @brief Format of texture object.
     */
    GLuint Internal_Format;

    /**
     * @brief Format of loaded image.
     */
    GLuint Image_Format;

    /**
     * @brief Wrapping mode on S axis.
     */
    GLuint Wrap_S;

    /**
     * @brief Wrapping mode on T axis.
     */
    GLuint Wrap_T;

    /**
     * @brief Filtering mode if texture pixels < screen pixels.
     */
    GLuint Filter_Min;

    /**
     * @brief Filtering mode if texture pixels > screen pixels.
     */
    GLuint Filter_Max;
};