﻿#pragma once
#include <functional>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace GameEngine
{
    class Window
    {
        public:
            typedef void (*WindowResizeCallbackFunction)(Window*);

            explicit Window(glm::ivec2 initialSize);
            void     DestroyGLWindow() const;
            ~Window();

            static void FramebufferSizeCallback(GLFWwindow* glWindow, int width, int height);

            void CreateContext();

            void SetFullscreen(bool fullscreen);

            void SetSize(glm::ivec2 newSize);

            void AddFramebufferSizeCallback(const std::function<void(Window*)>& callbackFunction);

            bool ShouldClose() const;
        
            glm::uvec2                                 GetSize() const;
            std::vector<std::function<void(Window*)>>& GetResizeCallbacks();
            static Window*                             GetCurrentWindow();
            GLFWwindow*                                GetGlWindow() const;

        private:
            static Window*                            _currentWindow;
            GLFWwindow*                               _glWindow = nullptr;
            glm::uvec2                                _size     = glm::uvec2(500);
            glm::uvec2                                _positionBeforeFullscreen;
            glm::uvec2                                _sizeBeforeFullscreen;
            std::vector<std::function<void(Window*)>> _resizeCallbacks;
    };
}
