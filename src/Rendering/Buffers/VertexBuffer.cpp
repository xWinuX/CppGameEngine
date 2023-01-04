#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned char* pVertices, const unsigned int stride, const unsigned int numVertices):
    _pVertices(pVertices),
    _stride(stride),
    _numVertices(numVertices)
{
    glGenBuffers(1, &_vertexBufferID);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_vertexBufferID);
    delete[] _pVertices;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, _numVertices * _stride, _pVertices, GL_STATIC_DRAW);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
