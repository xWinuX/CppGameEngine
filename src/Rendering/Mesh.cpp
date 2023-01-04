#include "Mesh.h"

Mesh::Mesh(VertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer, VertexBufferLayout* pVertexBufferLayout):
    _pVertexBuffer(pVertexBuffer),
    _pIndexBuffer(pIndexBuffer),
    _pVertexBufferLayout(pVertexBufferLayout) {}

Mesh::~Mesh()
{
    delete _pVertexBuffer;
    delete _pIndexBuffer;
    delete _pVertexBufferLayout;
}

VertexBuffer*       Mesh::GetVertexBuffer() const { return _pVertexBuffer; }
IndexBuffer*        Mesh::GetIndexBuffer() const { return _pIndexBuffer; }
VertexBufferLayout* Mesh::GetVertexBufferLayout() const { return _pVertexBufferLayout; }
