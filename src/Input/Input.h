#pragma once

#include "../Application.h"


namespace GameEngine
{
    namespace Input
    {
        class Input
        {
            private:
                static void Update();

            public:
                static bool GetKeyDown(int key);
                static bool GetKeyPressed(int key);

                friend Application;
        };
    }
}
