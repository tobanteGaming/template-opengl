#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "raw_model.hpp"

namespace tobanteGaming
{
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