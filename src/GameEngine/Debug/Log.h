﻿#pragma once
#include <string>

namespace GameEngine
{
    namespace Debug
    {
        class Log
        {
            public:
                static void Message(const std::string& message);
                static void Error(const std::string& message);
        };
    }
}
