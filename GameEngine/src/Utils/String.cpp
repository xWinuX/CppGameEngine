#include "GameEngine/Utils/String.h"

#include <algorithm>
#include <codecvt>
#include <fstream>
#include <string>

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


// Source (modified): ChatGPT
std::string String::ReplaceIncludeMacros(const std::string& filePath)
{
    std::string result;
    std::string line;

    std::ifstream in(filePath, std::ios::in | std::ios::binary);
    in.imbue(std::locale(in.getloc(), new std::codecvt_utf8_utf16<wchar_t, 0x10FFFF, std::consume_header>));

    char bom[3];
    in.read(bom, 3);
    if (bom[0] != static_cast<char>(0xEF) || bom[1] != static_cast<char>(0xBB) || bom[2] != static_cast<char>(0xBF)) {
        // If the file doesn't contain a BOM, seek back to the beginning of the file
        in.seekg(0);
    }
    
    std::string baseDir = filePath;
    std::replace(baseDir.begin(), baseDir.end(), '\\', '/');
    size_t lastSlash = baseDir.find_last_of('/');
    baseDir          = baseDir.substr(0, lastSlash);

    while (std::getline(in, line))
    {
        if (line.find("#include") == 0)
        {
            size_t      start        = line.find('"') + 1;
            size_t      end          = line.find('"', start);
            std::string includedFile = line.substr(start, end - start);

            std::string includedFilePath = baseDir + "/" + includedFile;

            std::string includedFileContents = ReplaceIncludeMacros(includedFilePath);

            result += includedFileContents + "\n";
        }
        else
        {
            result += line + "\n";
        }
    }
    
    return result;
}
