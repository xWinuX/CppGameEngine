#include "String.h"

using namespace GameEngine::Utils;

std::vector<std::string> String::SplitString(const std::string& str, const char delimiter, const unsigned baseOffset)
{
    std::vector<std::string> split;
    unsigned int             offset         = baseOffset;
    unsigned int             previousOffset = baseOffset;

    while (offset < str.length())
    {
        offset = str.find(delimiter, offset);

        // Break out of the loop if next find can't be found
        if (offset == std::string::npos) { offset = str.length(); }

        std::string sub = str.substr(previousOffset, (offset - previousOffset));
        split.push_back(sub);
        offset++;
        previousOffset = offset;
    }

    return split;
}
