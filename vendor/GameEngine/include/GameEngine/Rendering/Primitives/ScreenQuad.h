#pragma once
#include "GameEngine/Rendering/Primitive.h"
#include "glm/vec2.hpp"

namespace GameEngine
{
    namespace Rendering
    {
        namespace Primitives
        {
            class ScreenQuad
            {
                public:
                    static Primitive* GetPrimitive();

                private:
                    struct Vertex
                    {
                        glm::vec2 Position;
                        glm::vec2 UV;
                    };
            };
        }
    }
}
