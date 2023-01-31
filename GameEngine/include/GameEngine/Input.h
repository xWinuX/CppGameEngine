#pragma once
#include "GameEngine/Application.h"

namespace GameEngine
{
    class Input
    {
        friend Application;

        private:
            static void Update();

        public:
            static bool GetKeyDown(int key);
            static bool GetKeyPressed(int key);
            static glm::vec2 GetMousePosition();
    };
}
