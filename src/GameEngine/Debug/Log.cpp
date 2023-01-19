#include "Log.h"

#include <iostream>
#include <ostream>

using namespace GameEngine::Debug;

void Log::Message(const std::string& message)
{
    #if defined(_DEBUG)
    std::cout << message << std::endl;
    #endif
}

void Log::Error(const std::string& message)
{
    #if defined(_DEBUG)
    std::cerr << message << std::endl;
    #endif
}
