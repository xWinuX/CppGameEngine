#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include "Core/Window.h"

class Application
{
    private:
        Window* _window = nullptr;
    public:
        explicit Application();
        void Run(glm::ivec2 initialWindowSize);
        Window& GetWindow() const { return *_window; }
};
