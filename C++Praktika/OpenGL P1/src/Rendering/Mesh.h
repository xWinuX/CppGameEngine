#pragma once
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBufferLayout.h"

class Material;

struct Mesh
{
    public:
        VertexBuffer*       PVertexBuffer;
        IndexBuffer*        PIndexBuffer;
        VertexBufferLayout* PVertexBufferLayout;
};
