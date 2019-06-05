#include <fstream>
#include <iostream>
#include <sstream>

#include "3rd_party/stb_image.h"

#include "resource_manager.hpp"
#include "settings.hpp"
#include "shader_source.hpp"

namespace tobanteGaming
{
// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar* vShaderFile,
                                   const GLchar* fShaderFile,
                                   const GLchar* gShaderFile, std::string name)
{
    std::string v_fullPath = std::string(RESOURCE_PATH + vShaderFile);
    std::string f_fullPath = std::string(RESOURCE_PATH + fShaderFile);

    Shaders[name] = loadShaderFromFile(v_fullPath.c_str(), f_fullPath.c_str(),
                                       gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) { return Shaders[name]; }

Texture2D ResourceManager::LoadTexture(const GLchar* file, GLboolean alpha,
                                       std::string name)
{
    std::string fullPath = std::string(RESOURCE_PATH + file);
    Textures[name]       = loadTextureFromFile(fullPath.c_str(), alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (Properly) delete all shaders
    for (auto iter : Shaders)
    {
        glDeleteProgram(iter.second.ID);
    }
    // (Properly) delete all textures
    for (auto iter : Textures)
    {
        glDeleteTextures(1, &iter.second.ID);
    }
}

Shader ResourceManager::loadShaderFromFile(const GLchar* vShaderFile,
                                           const GLchar* fShaderFile,
                                           const GLchar* gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vCode;
    std::string fCode;
    std::string gCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Convert stream into string
        vCode = vShaderStream.str();
        fCode = fShaderStream.str();

        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            gCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    // Convert to GLchar
    const GLchar* vGLCode = vCode.c_str();
    const GLchar* fGLCode = fCode.c_str();
    const GLchar* gGLCode = gShaderFile != nullptr ? gCode.c_str() : nullptr;

    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vGLCode, fGLCode, gGLCode);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar* file,
                                               GLboolean alpha)
{
    // Create Texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format    = GL_RGBA;
    }
    // Load image
    int width, height, nrChannels;
    unsigned char* data  = stbi_load(file, &width, &height, &nrChannels, 0);
    //unsigned char* image = SOIL_load_image(
    //    file, &width, &height, 0,
    //    texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    // Now generate texture
    texture.Generate(width, height, data);
    // And finally free image data
    //SOIL_free_image_data(image);
    return texture;
}

}  // namespace tobanteGaming