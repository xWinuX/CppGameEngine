#include "Model.h"
#include <fstream>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../Debug/Log.h"

Model::Model(const std::string& filePath)
{
    std::ifstream stream(filePath, std::ios::in);

    // Check if file can be opened
    if (!stream)
    {
        Debug::Log::Error("Cannot open " + filePath);
        exit(1);
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec4> colors;

    std::string line;
    while (std::getline(stream, line))
    {
        if (line.length() == 0) { continue; }
       
        switch (line[0])
        {
            case 'o':
                // TODO: implement
                break;
            
            case 'v':
                if (line.length() == 1) { continue; }
                switch (line[1])
                {
                    case ' ':
                        const size_t xEndPos = line.find( ' ',2);
                        if (xEndPos == std::string::npos) { Debug::Log::Error("Invalid obj file " + filePath); }
                        Debug::Log::Error(std::to_string(xEndPos));
                        const float x = stof(line.substr(1, xEndPos));

                        
                        const size_t yEndPos = line.find( ' ',xEndPos);
                        if (yEndPos == std::string::npos) { Debug::Log::Error("Invalid obj file " + filePath); }
                        const float y = stof(line.substr(xEndPos+1, yEndPos));
        
                        const size_t zEndPos = line.find( ' ',yEndPos);
                        if (zEndPos == std::string::npos) { Debug::Log::Error("Invalid obj file " + filePath); }
                        const float z = stof(line.substr(yEndPos+1, zEndPos));
        
                        Debug::Log::Message(std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z));
                        
                        break;
                }

                break;
        }
    }

    stream.close();
}
