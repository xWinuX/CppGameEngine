#include "Stream.h"
#include "../Debug/Log.h"


Stream::Stream(const std::string& filePath):
    _stream(std::ifstream(filePath))
{
    if (!_stream) { Debug::Log::Error("Cannot open " + filePath); }
}

Stream::~Stream() { Close(); }

void Stream::Close() { if (_stream && _stream.is_open()) { _stream.close(); } }
