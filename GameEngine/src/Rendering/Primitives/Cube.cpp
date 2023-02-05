#include "GameEngine/Rendering/Primitives/Cube.h"

#include <glad/glad.h>

#include "GameEngine/Rendering/VertexBufferAttribute.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::Rendering::Primitives;


Primitive* Cube::GetPrimitive()
{
    VertexPositionColorUV vertices[] = {
        // Front
        {{-0.5f, -0.5f, 0.5f}, {0.0, 0.0, 0.0, 1.0}, {0.0f, 0.0f}}, // 0 Top Left
        {{0.5f, -0.5f, 0.5f}, {0.0, 0.0, 0.0, 1.0}, {1.0f, 0.0f}},  // 1 Top Right
        {{-0.5f, 0.5f, 0.5f}, {1.0, 1.0, 1.0, 1.0}, {0.0f, 1.0f}},  // 2 Bottom Left
        {{0.5f, 0.5f, 0.5f}, {1.0, 1.0, 1.0, 1.0}, {1.0f, 1.0f}},   // 3 Bottom Right

        // Back
        {{-0.5f, -0.5f, -0.5f}, {0.0, 0.0, 0.0, 0.0}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0, 0.0, 0.0, 0.0}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0, 1.0, 1.0, 1.0}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0, 1.0, 1.0, 1.0}, {1.0f, 1.0f}},

        // Right
        {{0.5f, -0.5f, -0.5f}, {0.0, 0.0, 0.0, 1.0}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0, 0.0, 0.0, 1.0}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0, 1.0, 1.0, 1.0}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0, 1.0, 1.0, 1.0}, {1.0f, 1.0f}},

        // Left
        {{-0.5f, -0.5f, -0.5f}, {0.0, 0.0, 0.0, 1.0}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0, 0.0, 0.0, 1.0}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0, 1.0, 1.0, 1.0}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {1.0, 1.0, 1.0, 1.0}, {1.0f, 1.0f}},

        // Top
        {{-0.5f, 0.5f, -0.5f}, {0.0, 0.0, 0.0, 1.0}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0, 0.0, 0.0, 1.0}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {1.0, 1.0, 1.0, 1.0}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0, 1.0, 1.0, 1.0}, {1.0f, 1.0f}},

        // Bottom
        {{-0.5f, -0.5f, -0.5f}, {0.0, 0.0, 0.0, 1.0}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0, 0.0, 0.0, 1.0}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {1.0, 1.0, 1.0, 1.0}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0, 1.0, 1.0, 1.0}, {1.0f, 1.0f}},
    };

    unsigned int indices[] = {
        // Front Face
        0, 1, 2, // First Triangle
        1, 3, 2, // Second Triangle

        // Back Face
        2 + 4, 1 + 4, 0 + 4, // First Triangle
        3 + 4, 1 + 4, 2 + 4, // Second Triangle

        // Right Face
        2 + 8, 1 + 8, 0 + 8, // First Triangle
        3 + 8, 1 + 8, 2 + 8, // Second Triangle

        // Left Face
        0 + 12, 1 + 12, 2 + 12, // First Triangle
        1 + 12, 3 + 12, 2 + 12, // Second Triangle

        // Top Face
        2 + 16, 1 + 16, 0 + 16, // First Triangle
        3 + 16, 1 + 16, 2 + 16, // Second Triangle

        // Bottom Face
        0 + 20, 1 + 20, 2 + 20, // First Triangle
        1 + 20, 3 + 20, 2 + 20, // Second Triangle
    };


    return new Primitive(
                         new VertexBuffer(reinterpret_cast<unsigned char*>(vertices), sizeof(VertexPositionColorUV), 24),
                         new IndexBuffer(reinterpret_cast<unsigned char*>(indices), sizeof(unsigned int), 36),
                         new VertexBufferLayout(new VertexBufferAttribute[]{
                                                    VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorUV), nullptr),
                                                    VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorUV), (GLvoid*)(3 * sizeof(float))),
                                                    VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorUV), (GLvoid*)(7 * sizeof(float)))
                                                }, 3)
                        );
}
