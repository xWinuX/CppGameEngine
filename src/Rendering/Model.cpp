#include "Model.h"
#include <fstream>
#include <random>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Vertex.h"
#include "../Components/Camera.h"
#include "../Debug/Log.h"

std::vector<std::string> splitString(const std::string& str, const char delimiter, const unsigned int baseOffset)
{
    std::vector<std::string> split;
    unsigned int             offset         = baseOffset;
    unsigned int             previousOffset = baseOffset;

    while (offset < str.length())
    {
        offset = str.find(delimiter, offset);

        // Break out of the loop if next find can't be found
        if (offset == std::string::npos)
        {
            offset = str.length();
        }
        
        Debug::Log::Message(std::to_string(offset));

        std::string sub = str.substr(previousOffset, (offset-previousOffset));
        Debug::Log::Message(sub);
        split.push_back(sub);
        offset++;
        previousOffset = offset;
    }

    return split;
}


template <typename T>
void splitString(const std::string& str, const unsigned int baseOffset, const char delimiter, T** pointerList, const unsigned int pointerListSize)
{
    unsigned int offset         = baseOffset;
    unsigned int previousOffset = baseOffset;
    for (unsigned int i = 0; i < pointerListSize; i++)
    {
        offset = str.find(delimiter, offset);

        if (offset == std::string::npos)
        {
            offset = str.length();
        }

        if (
            typeid(T) == typeid(int) ||
            typeid(T) == typeid(unsigned) ||
            typeid(T) == typeid(unsigned int)
        ) { **(pointerList + i) = stoi(str.substr(previousOffset, (offset-previousOffset))); }
        else if (typeid(T) == typeid(float)) { **(pointerList + i) = stof(str.substr(previousOffset, (offset-previousOffset))); }
        offset++;
        previousOffset = offset;
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
    
    std::vector<glm::vec3> positionList;
    std::vector<glm::vec2> uvList;
    std::vector<glm::vec3> normalList;
    std::vector<glm::vec4> colorList;

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
                {
                    // Skip if line length is 1
                    if (line.length() == 1) { continue; }

                    // Vec2 attributes
                    if (line[1] == 't') // vec2 (uvs)
                    {
                        glm::vec2 vec2           = glm::vec2(0.0);
                        float*    pVec2Coords[2] = {&vec2.x, &vec2.y};
                        splitString<float>(line, 3, ' ', pVec2Coords, 2);

                        Debug::Log::Message(std::to_string(vec2.x) + "," + std::to_string(vec2.y));

                        uvList.push_back(vec2);
                        continue;
                    }

                    // Vec3 attributes
                    glm::vec3 vec3           = glm::vec3(0.0f);
                    float*    pVec3Coords[3] = {&vec3.x, &vec3.y, &vec3.z};
                    if (line[1] == ' ') // Positions
                    {
                        splitString<float>(line, 2, ' ', pVec3Coords, 3);
                        positionList.push_back(vec3);
                    }
                    else if (line[1] == 'n') // Normals
                    {
                        splitString<float>(line, 3, ' ', pVec3Coords, 3);
                        normalList.push_back(vec3);
                    }

                    Debug::Log::Message(std::to_string(vec3.x) + "," + std::to_string(vec3.y) + "," + std::to_string(vec3.z));

                    break;
                }
            case 'f':
                Debug::Log::Message("before split");
                std::vector<std::string> vertices = splitString(line, ' ', 2);
                Debug::Log::Message("after split");

                for (const std::string& vertex : vertices)
                {
                    indexBuffer.push_back(indexBuffer.size());
                    unsigned int positionIndex = 0;
                    unsigned int uvIndex       = 0;
                    unsigned int normalIndex   = 0;

                    unsigned int* pVertexAttributes[] = {&positionIndex, &uvIndex, &normalIndex};
                    
                    Debug::Log::Message(vertex);
                    splitString(vertex, 0, '/', pVertexAttributes, 3);

                    Debug::Log::Message(std::to_string(positionIndex) + "," + std::to_string(uvIndex) + "," + std::to_string(normalIndex));
                    
                    vertexBuffer.emplace_back(positionList[positionIndex-1], uvList[uvIndex-1], normalList[normalIndex-1]);
                }

                break;
        }
    }
    stream.close();

    _vertexBuffer = new VertexBuffer(reinterpret_cast<unsigned char*>(vertexBuffer.data()), sizeof(VertexPositionUVNormal) ,vertexBuffer.size());
    _indexBuffer = new IndexBuffer(indexBuffer.data(), indexBuffer.size());
    _mesh = {_vertexBuffer, _indexBuffer, &_vertexBufferLayout};
}

Model::~Model()
{
    delete _vertexBuffer;
    delete _indexBuffer;
}

Mesh& Model::GetMesh()
{
    return _mesh;
}
