﻿#include "IndexBuffer.h"

#include "../OpenGL.h"
#include "../../Debug/Log.h"

IndexBuffer::IndexBuffer(unsigned char* pIndices, const unsigned numIndices, const GLenum indicesType):
    _pIndices(pIndices),
    _numIndices(numIndices),
    _indicesType(indicesType)
{
    glGenBuffers(1, &_indexBufferID);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &_indexBufferID);
}

unsigned int IndexBuffer::GetNumIndices() const { return _numIndices; }
GLenum       IndexBuffer::GetIndicesType() const { return _indicesType; }

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * OpenGL::TypeEnumLookup.at(_indicesType).Size, _pIndices, GL_STATIC_DRAW);
}
