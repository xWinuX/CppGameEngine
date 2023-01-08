#include "VertexBuffer.h"

#include "../Debug/Log.h"

using namespace GameEngine::Rendering;

VertexBuffer::VertexBuffer(unsigned char* pVertices, const unsigned int vertexSize, const unsigned int numVertices, const GLenum drawType):
    _pVertices(pVertices),
    _vertexSize(vertexSize),
    _numVertices(numVertices),
    _drawType(drawType)
{
    glGenBuffers(1, &_vertexBufferID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, _numVertices * _vertexSize, _pVertices, _drawType);
    Unbind();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_vertexBufferID);
    delete[] _pVertices;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::UpdateData(const unsigned char* data, const unsigned int numVertices)
{
    if (_drawType != GL_DYNAMIC_DRAW)
    {
        Debug::Log::Error("You can't update data on a static vertex buffer!");
        return;
    }

    _numVertices = numVertices;

    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, _numVertices * _vertexSize, data);
}
