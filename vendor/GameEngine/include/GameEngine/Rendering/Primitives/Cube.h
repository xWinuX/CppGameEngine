#pragma once
#include "GameEngine/Rendering/Primitive.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace GameEngine
{
    namespace Rendering
    {
        namespace Primitives
        {
            class Cube
            {
                public:
                    static Rendering::Primitive* GetPrimitive();

                private:
                    struct VertexPositionColorUV
                    {
                        glm::vec3 Position;
                        glm::vec4 Color;
                        glm::vec2 TexCoords;
                    };
            };
        }
    }
}
