#include "Log.h"

#include <iostream>
#include <ostream>

void Debug::Log::Message(const std::string& message)
{
    std::cout << message << std::endl;
}

void Debug::Log::Error(const std::string& message)
{
    std::cerr << message << std::endl;
}

