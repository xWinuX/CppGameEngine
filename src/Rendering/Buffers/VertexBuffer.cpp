#include "VertexBuffer.h"

#include <iostream>

#include "../../Debug/Log.h"

VertexBuffer::VertexBuffer(unsigned char* pVertices, const unsigned int stride, const unsigned int numVertices)
    : _pVertices(pVertices),
      _stride(stride),
      _numVertices(numVertices)
{
    glGenBuffers(1, &_vertexBufferID);
    std::cout << "vertCount: " << _numVertices << std::endl;
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_vertexBufferID);
    delete[] _pVertices;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    Debug::Log::Message("RENDER OPERATION: num vertices " + std::to_string(_numVertices * _stride));
    glBufferData(GL_ARRAY_BUFFER, _numVertices * _stride, _pVertices, GL_STATIC_DRAW);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
