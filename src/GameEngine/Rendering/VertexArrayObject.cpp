#include "VertexArrayObject.h"

using namespace GameEngine::Rendering;

VertexArrayObject::VertexArrayObject(const Primitive* primitive):
    VertexArrayObject(primitive->GetVertexBuffer(), primitive->GetIndexBuffer(), primitive->GetVertexBufferLayout()) {}

VertexArrayObject::VertexArrayObject(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout) :
    VertexArrayObject(vertexBufferLayout)
{
    _vertexBuffers.push_back(vertexBuffer);
    _pIndexBuffer = indexBuffer;
    Finalize();
}

VertexArrayObject::VertexArrayObject(VertexBufferLayout* pVertexBufferLayout)
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
    glDrawElements(GL_TRIANGLES, static_cast<int>(_pIndexBuffer->GetNumElements()), _pIndexBuffer->GetIndicesType(), static_cast<void*>(nullptr));
}

void VertexArrayObject::Render(const int numIndices, const unsigned int offset) const
{
    glDrawElements(GL_TRIANGLES, numIndices, _pIndexBuffer->GetIndicesType(), reinterpret_cast<void*>(offset*sizeof _pIndexBuffer->GetElementSize()));
}

void VertexArrayObject::Unbind() const
{
    glBindVertexArray(0);
}
