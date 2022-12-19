#pragma once
#include <string>
#include <vector>

#include "Mesh.h"


class Model
{
    private:
        VertexBufferAttribute               _vertexBufferAttributes[3] = {
            VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), nullptr),
            VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), (GLvoid*)(3 * sizeof(float))),
            VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), (GLvoid*)(5 * sizeof(float)))
        };
        VertexBufferLayout _vertexBufferLayout = VertexBufferLayout(_vertexBufferAttributes, 3);
        std::vector<Mesh*> _meshes;
    public:
        explicit Model(const std::string& filePath);
        ~Model();
        Mesh* GetMesh() const;
};
