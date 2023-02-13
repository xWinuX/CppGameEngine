#include "GameEngine/Rendering/Primitives/SkyboxCube.h"


#include <glm/vec3.hpp>

#include "tiny_gltf.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::Rendering::Primitives;

// Vertices and indices source: https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%2019%20-%20Cubemaps%20%26%20Skyboxes/Main.cpp
Primitive* SkyboxCube::GetPrimitive()
{
    glm::vec3 positions[] =
    {
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f},
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f}
    };

    unsigned int indices[] =
    {
        // Right
        1, 2, 6,
        6, 5, 1,

        // Left
        0, 4, 7,
        7, 3, 0,

        // Top
        4, 5, 6,
        6, 7, 4,

        // Bottom
        0, 3, 2,
        2, 1, 0,

        // Back
        0, 1, 5,
        5, 4, 0,

        // Front
        3, 7, 6,
        6, 2, 3
    };

    return new Primitive(
                         new VertexBuffer(reinterpret_cast<unsigned char*>(positions), sizeof(glm::vec3), 8),
                         new IndexBuffer(reinterpret_cast<unsigned char*>(indices), sizeof(unsigned int), 36),
                         new VertexBufferLayout(new VertexBufferAttribute[]{
                                                    VertexBufferAttribute(3,GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr)
                                                }, 1)
                        );
}
