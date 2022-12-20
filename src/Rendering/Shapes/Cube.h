#pragma once

#include "../Mesh.h"
#include "../Buffers/VertexBuffer.h"
#include "../Buffers/IndexBuffer.h"

class Cube
{
    private:
        static VertexBufferAttribute _vertexBufferAttributes[2];
        static VertexBufferLayout    _vertexBufferLayout;

        Mesh* _pMesh;

        VertexPositionUV*  _pCubeVertices;
        const unsigned int _numCubeVertices;

        unsigned int*      _pCubeIndices;
        const unsigned int _numCubeIndices;
    public:
        Cube();
        ~Cube();
        Mesh* GetMesh() const;
};
