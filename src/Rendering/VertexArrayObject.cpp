#include "VertexArrayObject.h"
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const Mesh* pMesh) : VertexArrayObject(pMesh->GetVertexBufferLayout())
{
    AddVertexBuffer(pMesh->GetVertexBuffer());
    SetIndexBuffer(pMesh->GetIndexBuffer());
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


void VertexArrayObject::SetIndexBuffer(IndexBuffer* pIndexBuffer)
{
    _pIndexBuffer = pIndexBuffer;
    pIndexBuffer->Bind();
}

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

void VertexArrayObject::Render() const
{
    glDrawElements(GL_TRIANGLES, static_cast<int>(_pIndexBuffer->GetNumIndices()), GL_UNSIGNED_INT, static_cast<void*>(nullptr));
}

void VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}
