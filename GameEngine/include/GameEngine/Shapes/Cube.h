#pragma once
#include "../Rendering/VertexBufferAttribute.h"
#include "../Rendering/VertexBufferLayout.h"
#include "../Rendering/Mesh.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace GameEngine
{
    namespace Shapes
    {
        class Cube
        {
            private:
                struct VertexPositionColorUV
                {
                    glm::vec3 Position;
                    glm::vec4 Color;
                    glm::vec2 TexCoords;
                };

                static Rendering::VertexBufferAttribute* _vertexBufferAttributes;
                static Rendering::VertexBufferLayout     _vertexBufferLayout;

                Rendering::Mesh* _pMesh;

                VertexPositionColorUV* _pCubeVertices;
                const unsigned int     _numCubeVertices;

                unsigned int*      _pCubeIndices;
                const unsigned int _numCubeIndices;

            public:
                Cube();
                ~Cube();
                Rendering::Mesh* GetMesh() const;
        };
    }
}
