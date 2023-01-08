#include "IndexBuffer.h"
#include "OpenGL.h"
#include "../Debug/Log.h"

using namespace GameEngine::Rendering;


IndexBuffer::IndexBuffer(unsigned char* pIndices, const GLenum indicesType, const unsigned int numIndices, const GLenum drawType):
    _pIndices(pIndices),
    _numIndices(numIndices),
    _indicesType(indicesType),
    _indexSize(),
    _drawType(drawType)
{
    Debug::Log::Message(std::to_string(indicesType));
    _indexSize = OpenGL::TypeEnumLookup.at(indicesType).Size;

    glGenBuffers(1, &_indexBufferID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * _indexSize, _pIndices, _drawType);
    Unbind();
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &_indexBufferID);
    delete[] _pIndices;
}

unsigned int IndexBuffer::GetNumIndices() const { return _numIndices; }
GLenum       IndexBuffer::GetIndicesType() const { return _indicesType; }
unsigned     IndexBuffer::GetIndexSize() const { return _indexSize; }

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::UpdateData(const unsigned char* data, const unsigned int numIndices)
{
    if (_drawType != GL_DYNAMIC_DRAW)
    {
        Debug::Log::Error("You can't update data on a static vertex buffer!");
        return;
    }

    _numIndices = numIndices;

    Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _numIndices * _indexSize, data);
}
