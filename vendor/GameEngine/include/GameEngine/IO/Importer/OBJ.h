#pragma once
#include <string>
#include <vector>
#include "../../Rendering/Mesh.h"
#include "../../Rendering/VertexBufferAttribute.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace GameEngine
{
    namespace IO
    {
        namespace Importer
        {
            class OBJ
            {
                private:
                    struct VertexPositionUVNormal
                    {
                        glm::vec3 Position;
                        glm::vec2 TexCoords;
                        glm::vec3 Normal;
                    };
                
                    static const std::vector<Rendering::VertexBufferAttribute> VertexBufferAttributes;

                    static void AddMesh(std::vector<VertexPositionUVNormal>& vertexBuffer, std::vector<unsigned int>& indexBuffer, std::vector<Rendering::Mesh*>& meshes);

                public:
                    static std::vector<GameEngine::Rendering::Mesh*> ImportModel(const std::string& filePath);
            };
        }
    }
}
