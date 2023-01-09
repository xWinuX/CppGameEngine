#pragma once
#include "../Rendering/VertexBufferAttribute.h"
#include "../Rendering/VertexBufferLayout.h"
#include "../Rendering/Vertex.h"
#include "../Rendering/Mesh.h"

namespace GameEngine
{
    namespace Shapes
    {
        class Cube
        {
            private:
                static Rendering::VertexBufferAttribute* _vertexBufferAttributes;
                static Rendering::VertexBufferLayout    _vertexBufferLayout;

                Rendering::Mesh* _pMesh;

                Rendering::VertexPositionColorUV*  _pCubeVertices;
                const unsigned int _numCubeVertices;

                unsigned int*      _pCubeIndices;
                const unsigned int _numCubeIndices;
            public:
                Cube();
                Rendering::Mesh* GetMesh() const;
        };
    }
}
