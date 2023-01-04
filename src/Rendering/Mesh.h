#pragma once
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBufferLayout.h"

class Mesh
{
    VertexBuffer*       _pVertexBuffer;
    IndexBuffer*        _pIndexBuffer;
    VertexBufferLayout* _pVertexBufferLayout;

    public:
        Mesh(VertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer, VertexBufferLayout* pVertexBufferLayout);
        ~Mesh();

        VertexBuffer*       GetVertexBuffer() const;
        IndexBuffer*        GetIndexBuffer() const;
        VertexBufferLayout* GetVertexBufferLayout() const;
};
