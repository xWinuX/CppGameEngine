#pragma once
#include <glad/glad.h>

struct MeshData
{
    public:
        const float*       PPositions;
        const GLubyte*     PIndices;
        const int NumPositions;
        const int NumIndices;
};
