#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <reactphysics3d/reactphysics3d.h>

#include "Scene.h"
#include "Window.h"

namespace GameEngine
{
    class Application
    {
        protected:
            GameEngine::Window _window = GameEngine::Window(glm::ivec2(800, 600));

        public:
            Application();
            virtual void Initialize(GameEngine::Scene& scene) {}

            void Run();

            virtual void CustomRun() {}
            virtual void OnEnd() {}
    };
}
