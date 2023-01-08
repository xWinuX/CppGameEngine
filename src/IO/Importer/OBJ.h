#pragma once
#include <string>
#include <vector>
#include "../../Rendering/Mesh.h"
#include "../../Rendering/Model.h"
#include "../../Rendering/Vertex.h"
#include "../../Rendering/VertexBufferAttribute.h"



namespace GameEngine
{
    namespace IO
    {
        namespace Importer
        {
            class OBJ
            {
                private:
                    static const std::vector<Rendering::VertexBufferAttribute> VertexBufferAttributes;

                    static void AddMesh(std::vector<Rendering::VertexPositionUVNormal>& vertexBuffer, std::vector<unsigned int>& indexBuffer, std::vector<Rendering::Mesh*>& meshes);

                public:
                    static std::vector<GameEngine::Rendering::Mesh*> ImportModel(const std::string& filePath);
            };
        }
    }
}
