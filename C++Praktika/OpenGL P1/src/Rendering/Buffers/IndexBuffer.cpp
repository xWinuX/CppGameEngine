#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLubyte* pIndices, const unsigned int numIndices)
{
    glGenBuffers(1, &_indexBufferID);
    _pIndices = pIndices;
    _numIndices = numIndices;
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &_indexBufferID);
}

unsigned int IndexBuffer::GetNumIndices() const
{
    return _numIndices;
}


void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(GLubyte), _pIndices, GL_STATIC_DRAW);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
