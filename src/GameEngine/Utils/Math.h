#pragma once

namespace GameEngine
{
    namespace Utils
    {
        class Math
        {
            public:
                static float Lerp(const float a, const float b, const float t);
                static float Sin01(const float x);
        };
    }
}
