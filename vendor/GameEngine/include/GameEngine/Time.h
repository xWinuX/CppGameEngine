#pragma once
#include "GameEngine/Application.h"

namespace GameEngine
{
    class Time
    {
        friend Application;

        public:
            static float GetDeltaTime();
            static float GetPhysicsDeltaTime();
            static float GetTimeSinceStart();

        private:
            static float _previousTimeSinceStart;
            static float _deltaTime;
            static void  Update();
    };
}
