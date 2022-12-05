#include "VertexArrayObject.h"

#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const Mesh* pMesh) : VertexArrayObject(pMesh->PVertexBufferLayout)
{
    AddVertexBuffer(pMesh->PVertexBuffer);
    SetIndexBuffer(pMesh->PIndexBuffer);
}

VertexArrayObject::VertexArrayObject(const VertexBufferLayout* pVertexBufferLayout)
{
    _pVertexBufferLayout = pVertexBufferLayout;
    glGenVertexArrays(1, &_vertexArrayObjectID);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &_vertexArrayObjectID);
}

void VertexArrayObject::AddVertexBuffer(VertexBuffer* pVertexBuffer) { _vertexBuffers.push_back(pVertexBuffer); }

void VertexArrayObject::SetIndexBuffer(IndexBuffer* pIndexBuffer) { _pIndexBuffer = pIndexBuffer; }

IndexBuffer* VertexArrayObject::GetIndexBuffer() const { return _pIndexBuffer; }

void VertexArrayObject::Bind() const
{
    glBindVertexArray(_vertexArrayObjectID);
}

void VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}
