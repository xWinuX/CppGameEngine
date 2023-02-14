#pragma once
#include "GameEngine/Application.h"

namespace GameEngine
{
    class Input
    {
        friend Application;

        public:
            static bool      GetKeyDown(int key);
            static bool      GetKeyPressed(int key);
            static glm::vec2 GetMousePosition();
            static glm::vec2 GetMouseDelta();

        private:
            static glm::vec2 _previousMousePosition;
            static void      Update();
    };
}
