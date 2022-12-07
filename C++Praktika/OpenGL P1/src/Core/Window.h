#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class Window
{
    private:
        typedef void (*WindowResizeCallbackFunction)(Window*);

        GLFWwindow*                               _glWindow = nullptr;
        glm::ivec2                                _size     = glm::ivec2(500);
        std::vector<WindowResizeCallbackFunction> _resizeCallbacks;
    public:
        explicit Window(glm::ivec2 initialSize);
        void     DestroyGLWindow() const;
        ~Window();

        static void FramebufferSizeCallback(GLFWwindow* glWindow, int width, int height);

        void CreateContext();

        void SetSize(glm::ivec2 newSize);

        void AddFramebufferSizeCallback(const WindowResizeCallbackFunction callbackFunction);

    
        glm::ivec2                                 GetSize() const;
        std::vector<WindowResizeCallbackFunction>& GetResizeCallbacks();
        GLFWwindow*                                GetGlWindow() const;
};
