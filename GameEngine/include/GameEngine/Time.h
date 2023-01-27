#pragma once
#include "GameEngine/Application.h"

namespace GameEngine
{
    class Time
    {
        friend Application;

        private:
            static float _previousTimeSinceStart;
            static float _deltaTime;
            static void  Update();

        public:
            static float GetDeltaTime();
            static float GetTimeSinceStart();
    };
}
