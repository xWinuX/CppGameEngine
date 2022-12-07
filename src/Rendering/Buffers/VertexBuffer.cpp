#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(VertexPos* pVertices, const unsigned int numVertices)
{
    glGenBuffers(1, &_vertexBufferID);
    _pVertices    = pVertices;
    _numVertices = numVertices;
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_vertexBufferID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, _numVertices * sizeof(VertexPos), _pVertices, GL_STATIC_DRAW);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
