#pragma once
#include <string>
#include <vector>

#include "Mesh.h"


class Model
{
    private:
        std::vector<VertexPositionUVNormal> vertexBuffer;
        std::vector<GLubyte>                indexBuffer;
        VertexBuffer*                       _vertexBuffer;
        IndexBuffer*                        _indexBuffer;
        VertexBufferAttribute               _vertexBufferAttributes[3] = {
            VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), nullptr),
            VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), (GLvoid*)(3 * sizeof(float))),
            VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), (GLvoid*)(5 * sizeof(float)))
        };
        VertexBufferLayout _vertexBufferLayout = VertexBufferLayout(_vertexBufferAttributes, 3);
        Mesh               _mesh;
    public:
        explicit Model(const std::string& filePath);
        ~Model();
        Mesh& GetMesh();
};
