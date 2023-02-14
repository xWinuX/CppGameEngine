#pragma once
#include <fstream>
#include <string>


namespace GameEngine
{
    namespace IO
    {
        class Stream
        {
            public:
                explicit Stream(const std::string& filePath);
                ~Stream();
                void           Close();
                std::ifstream& GetCStream() { return _stream; }
                std::string    GetFileContent();

            private:
                std::ifstream _stream;
        };
    }
}
