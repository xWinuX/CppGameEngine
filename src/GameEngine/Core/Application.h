#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <reactphysics3d/reactphysics3d.h> 

#include "Window.h"

class Application
{
    private:
        static GameEngine::Core::Window _window;

    public:
        Application();
        void                             Run() const;
        static GameEngine::Core::Window& GetWindow() { return _window; }
};
