#include "Stream.h"
#include "../Debug/Log.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace GameEngine::IO;

Stream::Stream(const std::string& filePath):
    _stream(std::ifstream(filePath))
{
    if (!_stream) { Debug::Log::Error("Cannot open " + filePath); }
}

Stream::~Stream() { Close(); }

void Stream::Close() { if (_stream && _stream.is_open()) { _stream.close(); } }

std::string Stream::GetFileContent()
{
    if (_stream.is_open())
    {
        std::string       line;
        std::stringstream ss;
        
        while (getline(_stream, line)) { ss << line << '\n'; }

        _stream.clear();
        
        return ss.str();
    }

    return "";
}
