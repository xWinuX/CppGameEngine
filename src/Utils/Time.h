#pragma once
#include "../Application.h"

class Time
{
    private:
        static float _previousTimeSinceStart;
        static float _deltaTime ;
        static void Update();
    public:
        static float GetDeltaTime();
        static float GetTimeSinceStart();

    friend Application;
};
