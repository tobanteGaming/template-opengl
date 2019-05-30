#include <fstream>
#include <sstream>

#include "game_level.hpp"
#include "settings.hpp"

void GameLevel::Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight)
{
    // Clear old data
    Bricks.clear();
    // Load from file
    GLuint tileCode;
    GameLevel level;
    std::string line;
    std::string fullPath = std::string(rr::RESOURCE_PATH + file);
    std::ifstream fstream(fullPath.c_str());
    std::vector<std::vector<GLuint>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line))  // Read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode)  // Read each word seperated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0) init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (GameObject& tile : Bricks)
        if (!tile.Destroyed) tile.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
    for (GameObject& tile : Bricks)
        if (!tile.IsSolid && !tile.Destroyed) return GL_FALSE;
    return GL_TRUE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
    // Calculate dimensions
    GLuint height = static_cast<GLuint>(tileData.size());
    // Note we can index vector at [0] since this
    // function is only called if height > 0
    GLuint width        = static_cast<GLuint>(tileData[0].size());
    GLfloat unit_width  = levelWidth / static_cast<GLfloat>(width),
            unit_height = static_cast<GLfloat>(levelHeight / height);

    // Initialize level tiles based on tileData
    for (GLuint y = 0; y < height; ++y)
    {
        for (GLuint x = 0; x < width; ++x)
        {
            // Check block type from level data (2D level array)
            if (tileData[y][x] == 1)  // Solid
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"),
                               glm::vec3(0.8f, 0.8f, 0.7f));
                obj.IsSolid = GL_TRUE;
                Bricks.push_back(obj);
            }
            else if (tileData[y][x] > 1)  // Non-solid; now determine its color
                                          // based on level data
            {
                glm::vec3 color = glm::vec3(1.0f);  // original: white
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
            }
        }
    }
}