#pragma once
#include <fstream>
#include <string>

class Stream
{
    private:
        std::ifstream _stream;
    public:
        explicit Stream(const std::string& filePath);
        ~Stream();
        void Close();
        std::ifstream& GetCStream() { return _stream; }
        std::string GetFileContent();
        
};
