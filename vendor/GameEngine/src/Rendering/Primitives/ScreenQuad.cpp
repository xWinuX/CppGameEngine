#include "GameEngine/Rendering/Primitives/ScreenQuad.h"

#include "glm/vec2.hpp"

using namespace GameEngine::Rendering;
using namespace GameEngine::Rendering::Primitives;

Primitive* ScreenQuad::GetPrimitive()
{
    Vertex* vertices = new Vertex[]{
        {{-1, -1}, {0, 0}}, // Top Left
        {{1, -1}, {1, 0}},  // Top Right
        {{-1, 1}, {0, 1}},  // Bottom Left
        {{1, 1}, {1, 1}},   // Bottom Right
    };

    unsigned int* indices = new unsigned int[]{
        0, 1, 2,
        1, 3, 2
    };

    return new Primitive(
                         new VertexBuffer(reinterpret_cast<unsigned char*>(vertices), sizeof(Vertex), 4),
                         new IndexBuffer(reinterpret_cast<unsigned char*>(indices), sizeof(unsigned int), 6),
                         new VertexBufferLayout(new VertexBufferAttribute[]{
                                                    VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr),
                                                    VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, UV)))
                                                }, 2));
}
