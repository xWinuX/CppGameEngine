#pragma once
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"

class Material;

struct Mesh
{
    public:
        VertexBuffer* PVertexBuffer;
        IndexBuffer* PIndexBuffer;
};
