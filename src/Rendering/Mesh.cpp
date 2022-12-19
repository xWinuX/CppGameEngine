#include "Mesh.h"

Mesh::Mesh(VertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer, VertexBufferLayout& vertexBufferLayout):
    _pVertexBuffer(pVertexBuffer),
    _pIndexBuffer(pIndexBuffer),
    _vertexBufferLayout(vertexBufferLayout)
{
}

Mesh::~Mesh()
{
    delete _pVertexBuffer;
    delete _pIndexBuffer;
}
