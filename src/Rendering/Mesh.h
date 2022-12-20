#pragma once
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBufferLayout.h"

class Mesh
{
    VertexBuffer*       _pVertexBuffer;
    IndexBuffer*        _pIndexBuffer;
    VertexBufferLayout& _vertexBufferLayout;
    public:
        Mesh(VertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer, VertexBufferLayout& vertexBufferLayout);
        ~Mesh();

        VertexBuffer* GetVertexBuffer() const { return _pVertexBuffer; }
        IndexBuffer*  GetIndexBuffer() const { return _pIndexBuffer; }
        VertexBufferLayout& GetVertexBufferLayout() const { return _vertexBufferLayout; }
};
