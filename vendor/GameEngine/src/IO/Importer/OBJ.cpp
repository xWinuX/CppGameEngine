#include "GameEngine/IO/Importer/OBJ.h"

#include "GameEngine/IO/Stream.h"
#include "GameEngine/Rendering/IndexBuffer.h"
#include "GameEngine/Rendering/VertexBuffer.h"
#include "GameEngine/Rendering/VertexBufferAttribute.h"
#include "GameEngine/Rendering/VertexBufferLayout.h"
#include "GameEngine/Utils/String.h"
#include "glm/vec4.hpp"


using namespace GameEngine::Rendering;
using namespace GameEngine::Utils;
using namespace GameEngine::IO::Importer;
using namespace GameEngine::IO;

const std::vector<VertexBufferAttribute> OBJ::VertexBufferAttributes = {
    VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), nullptr),
    VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), reinterpret_cast<GLvoid*>(3 * sizeof(float))),
    VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), reinterpret_cast<GLvoid*>(5 * sizeof(float)))
};

void OBJ::AddMesh(const std::string& name, std::vector<VertexPositionUVNormal>& vertexBuffer, std::vector<unsigned>& indexBuffer, std::vector<Mesh*>& meshes)
{
    // Create new mesh
    unsigned int* indices = new unsigned int[indexBuffer.size()];
    std::copy(indexBuffer.begin(), indexBuffer.end(), indices);

    VertexPositionUVNormal* vertices = new VertexPositionUVNormal[vertexBuffer.size()];
    std::copy(vertexBuffer.begin(), vertexBuffer.end(), vertices);


    VertexBufferAttribute* pVertexAttributes = new VertexBufferAttribute[3];
    std::copy(VertexBufferAttributes.begin(), VertexBufferAttributes.end(), pVertexAttributes);

    meshes.push_back(new Mesh(
                              name,
                              new VertexBuffer(reinterpret_cast<unsigned char*>(vertices), sizeof(VertexPositionUVNormal), vertexBuffer.size()),
                              new IndexBuffer(reinterpret_cast<unsigned char*>(indices), sizeof(unsigned int), indexBuffer.size()),
                              new VertexBufferLayout(pVertexAttributes, 3))
                    );
}

std::vector<GameEngine::Rendering::Mesh*> OBJ::ImportModel(const std::string& filePath)
{
    std::vector<Mesh*> meshes;

    Stream stream(filePath);

    std::vector<VertexPositionUVNormal> vertexBuffer;
    std::vector<unsigned int>           indexBuffer;
    std::vector<glm::vec3>              positionList;
    std::vector<glm::vec2>              uvList;
    std::vector<glm::vec3>              normalList;
    std::vector<glm::vec4>              colorList;

    std::string line;

    unsigned int positionIndexOffset = 0;
    unsigned int uvIndexOffset       = 0;
    unsigned int normalIndexOffset   = 0;
    unsigned int colorIndexOffset    = 0;
    std::string name;
    while (std::getline(stream.GetCStream(), line))
    {
        if (line.length() == 0) { continue; }

        switch (line[0])
        {
            case 'o': // New object
                name = line;
                if (!vertexBuffer.empty())
                {
                    positionIndexOffset += positionList.size();
                    uvIndexOffset += uvList.size();
                    normalIndexOffset += normalList.size();
                    colorIndexOffset += colorList.size();
                    AddMesh(name, vertexBuffer, indexBuffer, meshes);

                    vertexBuffer.clear();
                    indexBuffer.clear();
                    positionList.clear();
                    uvList.clear();
                    normalList.clear();
                    colorList.clear();
                }
                break;

            case 'v': // Vertex attributes
                {
                    // Skip if line length is 1
                    if (line.length() == 1) { continue; }

                    // Vec2 attributes
                    if (line[1] == 't') // vec2 (uvs)
                    {
                        glm::vec2 vec2           = glm::vec2(0.0);
                        float*    pVec2Coords[2] = {&vec2.x, &vec2.y};
                        String::SplitString<float>(line, 3, ' ', pVec2Coords, 2);

                        uvList.push_back(vec2);
                        continue;
                    }

                    // Vec3 attributes
                    glm::vec3 vec3           = glm::vec3(0.0f);
                    float*    pVec3Coords[3] = {&vec3.x, &vec3.y, &vec3.z};
                    if (line[1] == ' ') // Positions
                    {
                        String::SplitString<float>(line, 2, ' ', pVec3Coords, 3);
                        positionList.push_back(vec3);
                    }
                    else if (line[1] == 'n') // Normals
                    {
                        String::SplitString<float>(line, 3, ' ', pVec3Coords, 3);
                        normalList.push_back(vec3);
                    }


                    break;
                }
            case 'f': // Faces
                std::vector<std::string> vertices = String::SplitString(line, ' ', 2);

                for (const std::string& vertex : vertices)
                {
                    indexBuffer.push_back(indexBuffer.size());
                    unsigned int positionIndex = 0;
                    unsigned int uvIndex       = 0;
                    unsigned int normalIndex   = 0;

                    unsigned int* pVertexAttributes[] = {&positionIndex, &uvIndex, &normalIndex};


                    String::SplitString(vertex, 0, '/', pVertexAttributes, 3);

                    positionIndex -= positionIndexOffset;
                    uvIndex -= uvIndexOffset;
                    normalIndex -= normalIndexOffset;

                    vertexBuffer.push_back({positionList[positionIndex - 1], uvList[uvIndex - 1], normalList[normalIndex - 1]});
                }

                break;
        }
    }
    stream.Close();

    // Add last mesh
    AddMesh(name, vertexBuffer, indexBuffer, meshes);

    vertexBuffer.clear();
    indexBuffer.clear();
    positionList.clear();
    uvList.clear();
    normalList.clear();
    colorList.clear();

    return meshes;
}
