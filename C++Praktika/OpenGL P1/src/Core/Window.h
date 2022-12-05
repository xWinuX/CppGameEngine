#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class Window
{
    private:
        typedef void (*WindowResizeCallbackFunction)(Window*);
    
        GLFWwindow*                 _glWindow;
        glm::ivec2                  _size = glm::ivec2(0);
        std::vector<WindowResizeCallbackFunction> _resizeCallbacks;
    public:
        explicit Window(glm::ivec2 size);
        Window();
        ~Window();
    
        static void FramebufferSizeCallback(GLFWwindow* glWindow, int width, int height);

        std::vector<WindowResizeCallbackFunction>& GetResizeCallbacks() { return _resizeCallbacks; }
        GLFWwindow*                  GetGlWindow() const { return _glWindow; }

};
