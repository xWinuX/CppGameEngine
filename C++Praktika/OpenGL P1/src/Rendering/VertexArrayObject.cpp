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

VertexBuffer* VertexArrayObject::GetVertexBuffer() const
{
    return _vertexBuffers[0]; //TODO: This is wrong 
}

void VertexArrayObject::SetIndexBuffer(IndexBuffer* pIndexBuffer)
{
    _pIndexBuffer = pIndexBuffer;
    pIndexBuffer->Bind();
}

IndexBuffer* VertexArrayObject::GetIndexBuffer() const { return _pIndexBuffer; }

void VertexArrayObject::Finalize() const
{
    Bind();
    for (const VertexBuffer* vertexBuffer : _vertexBuffers) { vertexBuffer->Bind(); }
    _pVertexBufferLayout->Bind();
    _pIndexBuffer->Bind();
    Unbind();
}

void VertexArrayObject::Bind() const
{
    glBindVertexArray(_vertexArrayObjectID);
}

void VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}
