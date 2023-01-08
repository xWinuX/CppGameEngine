#include "Log.h"

#include <iostream>
#include <ostream>

using namespace GameEngine::Debug;

void Log::Message(const std::string& message)
{
    std::cout << message << std::endl;
}

void Log::Error(const std::string& message)
{
    std::cerr << message << std::endl;
}

