#pragma once

#include "core/common.hpp"

namespace tobanteGaming
{
class Window
{
public:
    Window() = default;
    ~Window();
    void init();

    inline bool isOpen() { return glfwWindowShouldClose(m_window) == 0; }
    inline void swapBuffers()
    {
        // Check and call events and swap the buffers
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

private:
    GLFWwindow* m_window;
};
}  // namespace tobanteGaming
