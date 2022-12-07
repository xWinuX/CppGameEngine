#pragma once

#include "../Mesh.h"
#include "../Buffers/VertexBuffer.h"
#include "../Buffers/IndexBuffer.h"

class Cube
{
    private:
        static VertexBufferAttribute _vertexBufferAttributes[1];
        static VertexBufferLayout _vertexBufferLayout;

        VertexBuffer _vertexBuffer;
        IndexBuffer  _indexBuffer;
        Mesh         _mesh;

        VertexPos _cubeVertices[8] = {
            // Front
            {{-1.0f, -1.0f, 1.0f}}, // 0 Front Top Left
            {{1.0f, -1.0f, 1.0f}},  // 1 Front Top Right
            {{-1.0f, 1.0f, 1.0f}},  // 2 Front Bottom Left
            {{1.0f, 1.0f, 1.0f}},   // 3 Front Bottom Right

            // Back
            {{-1.0f, -1.0f, -1.0f}}, // 0 Back Top Left
            {{1.0f, -1.0f, -1.0f}},  // 1 Back Top Right
            {{-1.0f, 1.0f, -1.0f}},  // 2 Back Bottom Left
            {{1.0f, 1.0f, -1.0f}},   // 3 Back Bottom Right
        };

        GLubyte _cubeIndices[36] = {
            // Front Face
            0, 1, 2, // First Triangle
            1, 3, 2, // Second Triangle

            // Right Face
            1, 5, 3, // First Triangle
            5, 7, 3, // Second Triangle

            // Left Face
            0, 6, 4, // First Triangle
            6, 0, 2, // Second Triangle

            // Top Face
            1, 0, 4, // First Triangle
            1, 4, 5, // Second Triangle

            // Bottom Face
            2, 3, 7, // First Triangle
            6, 2, 7, // Second Triangle

            // Back Face
            7, 5, 4, // First Triangle
            4, 6, 7  // Second Triangle
        };
    public:
        Cube();
        Mesh& GetMesh();
};
