#pragma once
#include <string>
#include <vector>

namespace GameEngine
{
    namespace Utils
    {
        class String
        {
            public:
                static std::vector<std::string> SplitString(const std::string& str, const char delimiter, const unsigned int baseOffset);

                template <typename T>
                static void SplitString(const std::string& str, const unsigned int baseOffset, const char delimiter, T** pointerList, const unsigned int pointerListSize)
                {
                    unsigned int offset         = baseOffset;
                    unsigned int previousOffset = baseOffset;
                    for (unsigned int i = 0; i < pointerListSize; i++)
                    {
                        offset = str.find(delimiter, offset);

                        if (offset == std::string::npos) { offset = str.length(); }

                        if (
                            typeid(T) == typeid(int) ||
                            typeid(T) == typeid(unsigned) ||
                            typeid(T) == typeid(unsigned int)
                        ) { **(pointerList + i) = stoi(str.substr(previousOffset, (offset - previousOffset))); }
                        else if (typeid(T) == typeid(float)) { **(pointerList + i) = stof(str.substr(previousOffset, (offset - previousOffset))); }
                        offset++;
                        previousOffset = offset;
                    }
                }

                static std::string ReplaceIncludeMacros(const std::string& filePath);
        };
    }
}
