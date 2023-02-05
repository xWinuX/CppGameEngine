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

            public:
                static Rendering::Primitive* GetPrimitive();
        };
    }
}
