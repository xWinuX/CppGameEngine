#pragma once
#include <string>
#include <vector>

#include "Mesh.h"
#include "Vertex.h"
#include "../Core/GameObject.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Model
        {
            private:
            const std::vector<VertexBufferAttribute> _vertexBufferAttributes = {
                VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), nullptr),
                VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), reinterpret_cast<GLvoid*>(3 * sizeof(float))),
                VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), reinterpret_cast<GLvoid*>(5 * sizeof(float)))
            };
            std::vector<Mesh*> _meshes;

            void AddMesh(
                std::vector<VertexPositionUVNormal>& vertexBuffer,
                std::vector<unsigned int>&           indexBuffer,
                std::vector<glm::vec3>&              positionList,
                std::vector<glm::vec2>&              uvList,
                std::vector<glm::vec3>&              normalList,
                std::vector<glm::vec4>&              colorList
            );

            public:
            explicit Model(const std::string& filePath);
            ~Model();
            Mesh*       GetMesh(unsigned int index) const;
            void        ImportObjModel(const std::string& filePath);
            void        ImportGLTFModel(const std::string& filePath);
        };
    }
}