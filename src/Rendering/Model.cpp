#include "Model.h"
#include <fstream>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Vertex.h"
#include "../Components/Camera.h"
#include "../Debug/Log.h"

void parseLine(const std::string& line, const unsigned int baseOffset, const char charToSplit, float** pointerList, const unsigned int pointerListSize)
{
    unsigned int offset         = baseOffset;
    unsigned int previousOffset = 2;
    for (unsigned int i = 0; i < pointerListSize; i++)
    {
        offset = line.find(charToSplit, offset);
        if (offset == std::string::npos) { Debug::Log::Message("Invalid obj file"); }
        **(pointerList + i) = stof(line.substr(previousOffset, offset));
        previousOffset      = offset;
    }
}

Model::Model(const std::string& filePath)
{
    std::ifstream stream(filePath, std::ios::in);

    // Check if file can be opened
    if (!stream)
    {
        Debug::Log::Error("Cannot open " + filePath);
        exit(1);
    }

    std::vector<VertexPositionUVNormal> vertexBuffer;
    std::vector<unsigned int> indexBuffer;
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
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

                if (line[1] == 't') // vec2 (uvs)
                {
                    glm::vec2 vec2 = glm::vec2(0.0);
                    float* pVec2Coords[2] = {&vec2.x, &vec2.y};
                    parseLine(line, 2, ' ', pVec2Coords, 2);

                    uvs.push_back(vec2);
                }
                else // vec3 (positions, normals)
                {
                    glm::vec3 vec3 = glm::vec3(0.0f);
                    float* pVec3Coords[3] = {&vec3.x, &vec3.y, &vec3.z};
                    parseLine(line, 2, ' ', pVec3Coords, 3);

                    Debug::Log::Message(std::to_string(vec3.x) + "," + std::to_string(vec3.y) + "," + std::to_string(vec3.z));

                    if (line[1] == ' ') { vertices.push_back(vec3); }
                    else { normals.push_back(vec3); }
                }
                break;
            case 'f':
                
                break;
        }
    }

    stream.close();
}
