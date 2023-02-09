#include "GameEngine/Rendering/VertexArrayObject.h"

using namespace GameEngine::Rendering;

VertexArrayObject::VertexArrayObject(const Primitive* primitive):
    VertexArrayObject(primitive->GetVertexBuffer(), primitive->GetIndexBuffer(), primitive->GetVertexBufferLayout()) {}

VertexArrayObject::VertexArrayObject(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout, const bool finalize) :
    VertexArrayObject()
{
    AddVertexBuffer(vertexBuffer, vertexBufferLayout);
    _indexBuffer = indexBuffer;
    if (finalize) { Finalize(); }
}

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &_vertexArrayObjectID);
}

VertexArrayObject::~VertexArrayObject()
{
    _vertexBuffers.clear();
    glDeleteVertexArrays(1, &_vertexArrayObjectID);
}

void VertexArrayObject::AddVertexBuffer(VertexBuffer* vertexBuffer, VertexBufferLayout* vertexBufferLayout)
{
    _vertexBuffers.push_back(vertexBuffer);
    _vertexBufferLayouts.push_back(vertexBufferLayout);
}


void VertexArrayObject::SetIndexBuffer(IndexBuffer* indexBuffer)
{
    _indexBuffer = indexBuffer;
    indexBuffer->Bind();
}

void VertexArrayObject::Finalize() const
{
    Bind();

    unsigned int offset = 0;
    for (unsigned int i = 0; i < _vertexBuffers.size(); i++)
    {
        _vertexBuffers[i]->Bind();
        _vertexBufferLayouts[i]->Bind(offset);
        offset += _vertexBufferLayouts[i]->GetNumVertexBufferAttributes();
    }

    _indexBuffer->Bind();

    Unbind();
}

void VertexArrayObject::Bind() const
{
    glBindVertexArray(_vertexArrayObjectID);
}

void VertexArrayObject::Draw() const
{
    Debug::Log::Message("Num elements: " + std::to_string(_indexBuffer->GetNumElements()));
    Debug::Log::Message("indices type: " + std::to_string(_indexBuffer->GetIndicesType()));
    glDrawElements(GL_TRIANGLES, static_cast<int>(_indexBuffer->GetNumElements()), _indexBuffer->GetIndicesType(), nullptr);
    Debug::Log::Message("after draw call");

}

void VertexArrayObject::Draw(const int numIndices, const unsigned int offset) const
{
    glDrawElements(GL_TRIANGLES, numIndices, _indexBuffer->GetIndicesType(), reinterpret_cast<void*>(offset * _indexBuffer->GetElementSize()));
}

void VertexArrayObject::DrawInstanced(const int numIndices, const int instanceCount) const
{
    glDrawElementsInstanced(GL_TRIANGLES, numIndices, _indexBuffer->GetIndicesType(), nullptr, instanceCount);
}

void VertexArrayObject::Unbind() const
{
    glBindVertexArray(0);
}
