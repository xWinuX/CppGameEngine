#include "VertexArrayObject.h"

using namespace GameEngine::Rendering;

VertexArrayObject::VertexArrayObject(const Mesh* pMesh) : VertexArrayObject(pMesh->GetVertexBufferLayout())
{
    AddVertexBuffer(pMesh->GetVertexBuffer());
    SetIndexBuffer(pMesh->GetIndexBuffer());
}

VertexArrayObject::VertexArrayObject( VertexBuffer* pVertexBuffer,  IndexBuffer* pIndexBuffer, const VertexBufferLayout* pVertexBufferLayout) : VertexArrayObject(pVertexBufferLayout)
{
    _vertexBuffers.push_back(pVertexBuffer);
    _pIndexBuffer = pIndexBuffer;
    Finalize();
}

VertexArrayObject::VertexArrayObject(const VertexBufferLayout* pVertexBufferLayout)
{
    _pVertexBufferLayout = pVertexBufferLayout;
    glGenVertexArrays(1, &_vertexArrayObjectID);
}

VertexArrayObject::~VertexArrayObject()
{
    _vertexBuffers.clear();
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
    glDrawElements(GL_TRIANGLES, static_cast<int>(_pIndexBuffer->GetNumIndices()), _pIndexBuffer->GetIndicesType(), static_cast<void*>(nullptr));
}

void VertexArrayObject::Unbind() const
{
    glBindVertexArray(0);
}
