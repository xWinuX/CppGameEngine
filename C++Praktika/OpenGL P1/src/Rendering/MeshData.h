#pragma once
#include <glad/glad.h>

struct MeshData
{
    public:
        const float*       pPositions;
        const GLubyte*     pIndices;
        const int numPositions;
        const int numIndices;
};
